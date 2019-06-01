/*
  based on
  https://github.com/dspinellis/cscout/blob/084d64dc7a0c5466dc2d505c1ca16fb303eb2bf1/src/macro.cpp
*/



#include "Macro.h"
#include "StringEx.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "PPToken.h"
#include <stdio.h>
#include "Mem.h"

struct Macro* Macro_Create(void) /*@default*/
{
    struct Macro* p = (struct Macro*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Name = NULL;
        p->bIsFunction = false;
        TokenArray_Init(&p->TokenSequence);
        TokenArray_Init(&p->FormalArguments);
        p->FileIndex = 0;
    }
    return p;
}

void Macro_Destroy(struct Macro* p) /*@default*/
{
    Free((void*)p->Name);
    TokenArray_Destroy(&p->TokenSequence);
    TokenArray_Destroy(&p->FormalArguments);
}

void Macro_Delete(struct Macro* p) /*@default*/
{
    if (p != NULL)
    {
        Macro_Destroy(p);
        Free((void*)p);
    }
}


bool FillIn(struct TokenArray* ts,
            bool get_more,
            struct TokenArray* removed);

void Glue(const struct TokenArray* lsI,
          const struct TokenArray* rsI,
          struct TokenArray* out);

// Return a new token sequence with hs added to the hide set of every element of ts
void HidenSetAdd(const struct TokenSet* hs,
                 const struct TokenArray* ts,
                 struct TokenArray* pOut)
{
    TokenArray_Clear(pOut);


    for (int i = 0; i < ts->Size; i++)
    {
        struct PPToken* t = ts->pItems[i];

        for (int k = 0; k < hs->Size; k++)
        {
            TokenSet_PushUnique(&t->HiddenSet, PPToken_Clone(hs->pItems[k]));
        }

        TokenArray_PushBack(pOut, PPToken_Clone(t));
    }

    //printf("hsadd returns: ");
    TokenArray_Print(pOut);
    //printf("\n");
}

void ExpandMacro(const struct TokenArray* pTokenSequence,
                 const struct MacroMap* macros,
                 bool get_more,
                 bool skip_defined,
                 bool evalmode,
                 struct Macro* caller,
                 struct TokenArray* pOutputSequence);

/*
Retorna o indice do primeiro token que não for espaço
a partir e incluindo o indice start.
Return -1 se não achar.
*/
int FindNoSpaceIndex(const struct TokenArray* pArray, int start)
{
    int result = -1;

    for (int i = start; i < pArray->Size; i++)
    {
        if (!PPToken_IsSpace(pArray->pItems[i]))
        {
            result = i;
            break;
        }
    }

    return result;
}

// Return s with all \ and " characters \ escaped
void AppendEscaped(struct StrBuilder* strBuilder,
                   const char* source)
{
    while (*source)
    {
        switch (*source)
        {
            case '\\':
            case '"':
                StrBuilder_AppendChar(strBuilder, '\\');

                // FALTHROUGH
            default:
                StrBuilder_AppendChar(strBuilder, *source);
        }

        source++;
    }
}

/*
* Convert a list of tokens into a char as specified by the # operator
* Multiple spaces are converted to a single space, \ and " are
* escaped
*/
void AppendStringize(struct StrBuilder* strBuilder, const struct TokenArray* ts)
{
    /*
    Each occurrence of white space between the arguments
    preprocessing tokens becomes a single space character in
    the character char literal.
    */

    /*
    White space before the first preprocessing token and after the
    last preprocessing token composing the argument is deleted.
    */

    StrBuilder_Append(strBuilder, "\"");

    bool seen_space = true;   // To delete leading spaces

    for (int i = 0; i < ts->Size; i++)
    {
        struct PPToken* pToken = ts->pItems[i];

        if (PPToken_IsSpace(pToken))
        {
            if (seen_space)
                continue;

            else
                seen_space = true;

            StrBuilder_Append(strBuilder, " ");
        }

        else if (PPToken_IsStringLit(pToken))
        {
            seen_space = false;
            StrBuilder_Append(strBuilder, "\\\"");
            AppendEscaped(strBuilder, pToken->Lexeme);
            StrBuilder_Append(strBuilder, "\\\"");
        }

        else if (PPToken_IsCharLit(pToken))
        {
            seen_space = false;
            StrBuilder_AppendChar(strBuilder, '\'');
            AppendEscaped(strBuilder, pToken->Lexeme);
            StrBuilder_AppendChar(strBuilder, '\'');
        }

        else
        {
            seen_space = false;
            StrBuilder_Append(strBuilder, pToken->Lexeme);
        }
    }

    StrBuilder_Append(strBuilder, "\"");

    // Remove trailing spaces
    StrBuilder_Trim(strBuilder);
}


/*
* Substitute the arguments args appearing in the input sequence is
* Result is created in the output sequence os and finally has the specified
* hide set added to it, before getting returned.
*/
void SubstituteArgs(struct Macro* pMacro,
                    const struct MacroMap* macros,
                    const struct TokenArray* isOriginal,   //macro
                    const struct TokenArrayMap* args,
                    struct TokenSet* hs,
                    bool skip_defined,
                    bool evalmode,
                    struct Macro* pCaller,
                    struct TokenArray* pOutputSequence)
{
    TokenArray_Clear(pOutputSequence);

    //Trabalha com uma copia
    struct TokenArray is = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&is, isOriginal);

    struct TokenArray os = TOKENARRAY_INIT;

    struct PPToken* head = NULL;
    while (is.Size > 0)
    {

        //printf("subst: is=");
        TokenArray_Print(&is);
        //printf(" os=");
        TokenArray_Print(&os);
        //printf("\n");

        //assert(head == NULL);
        head = TokenArray_PopFront(&is);

        if (PPToken_IsStringizingOp(head))
        {
            /*
            Each # preprocessing token in the replacement list for
            a function-like macro shall be followed by a parameter
            as the next preprocessing token in the replacement list.
            */

            // Stringizing operator
            int idx = FindNoSpaceIndex(&is, 0);
            struct TokenArray* aseq;

            if (idx != -1 &&
                args != NULL &&
                TokenArrayMap_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
            {
                /*
                If, in the replacement list, a parameter is immediately
                preceded by a # preprocessing token, both are replaced
                by a single character char literal preprocessing token that
                contains the spelling of the preprocessing token sequence
                for the corresponding argument.
                */
                struct StrBuilder strBuilder = STRBUILDER_INIT;
                AppendStringize(&strBuilder, aseq);
                TokenArray_Erase(&is, 0, idx + 1);

                //TODO token tipo?
                TokenArray_PushBack(&os, PPToken_Create(strBuilder.c_str, PPTokenType_Other));
                StrBuilder_Destroy(&strBuilder);

                PPToken_Delete(head);
                head = NULL;
                continue;
            }

        }

        else if (PPToken_IsConcatOp(head))
        {

            /*
            If, in the replacement list of a function-like macro,
            a parameter is immediately preceded or followed by
            a ## preprocessing token, the parameter is replaced by
            the corresponding arguments preprocessing token sequence;
            */
            int idx = FindNoSpaceIndex(&is, 0);

            if (idx != -1)
            {
                struct TokenArray* aseq;

                if (TokenArrayMap_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
                {
                    TokenArray_Erase(&is, 0, idx + 1);

                    // Only if actuals can be empty
                    if (aseq->Size > 0)
                    {
                        struct TokenArray os2 = TOKENARRAY_INIT;
                        Glue(&os, aseq, &os2);
                        TokenArray_Swap(&os2, &os);
                        TokenArray_Destroy(&os2);
                    }
                }

                else
                {
                    struct TokenArray t = TOKENARRAY_INIT;
                    TokenArray_PushBack(&t, PPToken_Clone(is.pItems[idx]));
                    TokenArray_Erase(&is, 0, idx + 1);

                    struct TokenArray os2 = TOKENARRAY_INIT;
                    Glue(&os, &t, &os2);
                    TokenArray_Swap(&os2, &os);
                    TokenArray_Destroy(&os2);
                    TokenArray_Destroy(&t);
                }

                PPToken_Delete(head);
                head = NULL;

                continue;
            }
        }

        else
        {
            int idx = FindNoSpaceIndex(&is, 0);

            if (idx != -1 &&
                PPToken_IsConcatOp(is.pItems[idx]))
            {
                /*
                * Implement the following gcc extension:
                *  "`##' before a
                *   rest argument that is empty discards the preceding sequence of
                *   non-whitespace characters from the macro definition.  (If another macro
                *   argument precedes, none of it is discarded.)"
                * Otherwise, break to process a non-formal argument in the default way
                */
                struct TokenArray* aseq;

                if (!TokenArrayMap_Lookup(args, head->Lexeme, &aseq))
                {
                    /*
                    if (m.get_is_vararg())
                    {
                    ti2 = find_nonspace(ti + 1, is.end());

                    if (ti2 != is.end() && (ai = find_formal_argument(args, *ti2)) != args.end() && ai->second.size() == 0)
                    {
                    // All conditions satisfied; discard elements:
                    // <non-formal> <##> <empty-formal>
                    is.erase(is.begin(), ++ti2);
                    continue;
                    }
                    }
                    */
                    // Non-formal arguments don't deserve special treatment
                    TokenArray_PushBack(&os, head);
                    head = NULL; //moved
                }
                else
                {
                    // Paste but not expand LHS, RHS

                    // Only if actuals can be empty
                    if (aseq->Size == 0)
                    {
                        // Erase including ##
                        TokenArray_Erase(&is, 0, idx + 1);

                        int idx2 = FindNoSpaceIndex(&is, 0);

                        if (idx2 != -1)
                        {
                            struct TokenArray* aseq2;

                            if (!TokenArrayMap_Lookup(args, is.pItems[idx2]->Lexeme, &aseq2))
                            {
                                // Erase the ## RHS
                                TokenArray_Erase(&is, 0, idx + 1);
                                TokenArray_AppendCopy(&os, aseq);
                            }
                        }
                    }

                    else
                    {
                        // Erase up to ##
                        TokenArray_Print(&is);
                        //printf("-\n");
                        TokenArray_Erase(&is, 0, idx);
                        TokenArray_Print(&is);
                        //printf("-\n");
                        TokenArray_AppendCopy(&os, aseq);
                    }
                }

                PPToken_Delete(head);
                head = NULL;

                continue;
            }

            struct TokenArray* argseq = NULL;

            if (args != NULL &&
                TokenArrayMap_Lookup(args, head->Lexeme, &argseq))
            {
                //expand head
                struct TokenArray expanded = TOKENARRAY_INIT;
                ExpandMacro(argseq, macros, false, skip_defined, evalmode, pCaller, &expanded);
                TokenArray_AppendMove(&os, &expanded);
                TokenArray_Destroy(&expanded);

                PPToken_Delete(head);
                head = NULL;

                continue;
            }
        }

        TokenArray_PushBack(&os, head);
        head = NULL; //moved
    }
    //assert(head == NULL);
    struct TokenArray os2 = TOKENARRAY_INIT;
    HidenSetAdd(hs, &os, &os2);

    TokenArray_Swap(pOutputSequence, &os2);

    TokenArray_Destroy(&os);
    TokenArray_Destroy(&os2);
    TokenArray_Destroy(&is);
}

/*
* Return a macro argument token from tokens
* Used by gather_args.
* If get_more is true when tokens is exhausted read using pdtoken::getnext_noexpand
* (see explanation on that method's comment for why we use pdtoken, rather than pltoken)
* Leave in tokens the first token not gathered.
* If want_space is true return spaces, otherwise discard them
*/
void ArgToken(struct TokenArray* tokens,
              bool get_more,
              bool want_space,
              struct PPToken* token)
{
    struct PPToken* pToken = TokenArray_PopFront(tokens);
    PPToken_Swap(pToken, token);
    PPToken_Delete(pToken);
    pToken = NULL;

    /*  if (want_space)
      {
        if (tokens->Size > 0)
        {
        Token *pToken = TokenArray_PopFront(tokens);
        PPToken_Swap(pToken, token);
        PPToken_Destroy(pToken);
          return;
        }

        else if (get_more)
        {
          //Pdtoken t;
          //t.getnext_noexpand();
          //return (t);
        }

      else
      {
        String2_Set(&token->Lexeme, NULL);
        //return Ptoken(EOF, "");
      }
      }

      else
      {
        while (tokens->Size > 0 && PPToken_IsSpace(tokens->pItems[0]))
        {
        Token* p = TokenArray_PopFront(tokens);
        PPToken_Delete(p);
        }

        if (tokens->Size > 0)
        {
        Token* p = TokenArray_PopFront(tokens);
        PPToken_Swap(p, token);
        PPToken_Delete(p);

          return;
        }

        else if (get_more)
        {
          //Pdtoken t;

          //do
          //{
            //t.getnext_noexpand_nospc();
          //}
          //while (t.get_code() != EOF && t.is_space());

          //return (t);
        }

      else
      {
        String2_Set(&token->Lexeme, NULL);
        //return Ptoken(EOF, "");
      }
      }  */
}

/*
* Get the macro arguments specified in formal_args, initiallly by
* removing them from tokens, then, if get_more is true,
from pdtoken.getnext_noexpand.
* The opening bracket has already been gathered.
* Build the map from formal name to argument value args.
* Return in close the closing bracket token (used for its hideset)
* Return true if ok, false on error.
*/
bool GatherArgs(const char* name,
                struct TokenArray* tokens,
                const struct TokenArray* formal_args,
                struct TokenArrayMap* args,
                bool get_more,
                bool is_vararg,
                struct PPToken* close)
{
    struct PPToken t = TOKEN_INIT;

    for (int i = 0; i < formal_args->Size; i++)
    {
        struct TokenArray* pV = TokenArray_Create();

        TokenArrayMap_SetAt(args,
                            formal_args->pItems[i]->Lexeme,
                            pV);

        char terminate;

        if (i + 1 == formal_args->Size)
        {
            terminate = ')';
        }

        else if (is_vararg && i + 2 == formal_args->Size)
        {
            // Vararg last argument is optional; terminate with ) or ,
            terminate = '.';
        }

        else
        {
            terminate = ',';
        }

        int bracket = 0;

        // Get a single argument
        for (;;)
        {
            ArgToken(tokens, get_more, true, &t);
            //printf("tokens=");
            TokenArray_Print(tokens);
            //printf("\n");

            if (bracket == 0 && (
                (terminate == '.' && (PPToken_IsChar(&t, ',') || PPToken_IsChar(&t, ')'))) ||
                (terminate != '.' && PPToken_IsChar(&t, terminate))))
            {
                break;
            }

            if (PPToken_IsChar(&t, '('))
            {
                bracket++;
            }

            else if (PPToken_IsChar(&t, ')'))
            {
                bracket--;
            }

            else if (PPToken_IsChar(&t, '\0')) //EOF
            {
                /*
                * @error
                * The end of file was reached while
                * gathering a macro's arguments
                */
                //printf("macro [%s] EOF while reading function macro arguments", name);
                return (false);
            }

            else
            {
            }


            TokenArray_PushBack(pV, PPToken_Clone(&t));
        }

        //printf("Gather args returns: ");
        TokenArray_Print(pV);
        //printf("\n");

        // Check if varargs last optional argument was not supplied
        if (terminate == '.' && PPToken_IsChar(&t, ')'))
        {
            i++;
            struct TokenArray* pV2 = TokenArray_Create();

            TokenArrayMap_SetAt(args,
                                formal_args->pItems[i]->Lexeme,
                                pV2);

            // Instantiate argument with an empty value list
            //args[(*i).get_val()];
            break;
        }

        Free(close->Lexeme);
        close->Lexeme = StrDup(t.Lexeme);
    }

    if (formal_args->Size == 0)
    {
        ArgToken(tokens, get_more, false, &t);

        if (PPToken_IsChar(&t, ')'))
        {
            /*
            * @error
            * The arguments to a function-like macro did
            * not terminate with a closing bracket
            */
            //printf("macro [%s] close bracket expected for function-like macro", name);
            return (false);
        }
    }


    PPToken_Destroy(&t);

    return (true);
}

/*
* Remove from tokens and return the elements comprising the arguments to the defined
* operator, * such as "defined X" or "defined(X)"
* This is the rule when processing #if #elif expressions
*/
void GatherDefinedOperator(struct TokenArray* tokens,
                           const struct MacroMap* macros,
                           struct TokenArray* result)
{
    //struct TokenArray tokens = TOKENARRAY_INIT;
    //TokenArray_AppendCopy(&tokens, tokensIn);

    // Skip leading space
    while (PPToken_IsSpace(tokens->pItems[0]))
    {
        struct PPToken* pp = TokenArray_PopFront(tokens);
        TokenArray_PushBack(result, pp);
    }

    if ((PPToken_IsIdentifier(tokens->pItems[0])))
    {
        // defined X form
        if (MacroMap_Find(macros, tokens->pItems[0]->Lexeme) != NULL)
        {
            struct PPToken* pp0 = TokenArray_PopFront(tokens);

            Free(pp0->Lexeme);
            pp0->Lexeme = StrDup("1");


            TokenArray_PushBack(result, pp0);
        }

        else
        {
            struct PPToken* pp0 = TokenArray_PopFront(tokens);
            Free(pp0->Lexeme);
            pp0->Lexeme = StrDup("0");

            TokenArray_PushBack(result, pp0);
        }

        return;
    }

    else if ((PPToken_IsChar(tokens->pItems[0], '(')))
    {
        // defined (X) form


        PPToken_Delete(TokenArray_PopFront(tokens));




        // Skip spaces
        while (PPToken_IsSpace(tokens->pItems[0]))
        {
            struct PPToken* pp = TokenArray_PopFront(tokens);
            TokenArray_PushBack(result, pp);
        }

        if (!PPToken_IsIdentifier(tokens->pItems[0]))
        {
            //goto error;
        }

        if (MacroMap_Find(macros, tokens->pItems[0]->Lexeme) != NULL)
        {
            struct PPToken* pp0 = TokenArray_PopFront(tokens);

            Free(pp0->Lexeme);
            pp0->Lexeme = StrDup("1");

            TokenArray_PushBack(result, pp0);
        }

        else
        {
            struct PPToken* pp0 = TokenArray_PopFront(tokens);

            Free(pp0->Lexeme);
            pp0->Lexeme = StrDup("0");

            TokenArray_PushBack(result, pp0);
        }

        //PPToken* pp = TokenArray_PopFront(&tokens);
        //TokenArray_PushBack(result, pp);

        // Skip spaces
        while (PPToken_IsSpace(tokens->pItems[0]))
        {
            struct PPToken* pp = TokenArray_PopFront(tokens);
            TokenArray_PushBack(result, pp);
        }

        if (!PPToken_IsChar(tokens->pItems[0], ')'))
        {
            //goto error;
        }

        PPToken_Delete(TokenArray_PopFront(tokens));
        //TokenArray_PushBack(result, pp);

        return;
    }

    else
    {
    }
}


void ExpandMacro(const struct TokenArray* tsOriginal,
                 const struct MacroMap* macros,
                 bool get_more,
                 bool skip_defined,
                 bool evalmode,
                 struct Macro* caller,
                 struct TokenArray* pOutputSequence2)
{
    TokenArray_Clear(pOutputSequence2);

    struct TokenArray r = TOKENARRAY_INIT;

    struct TokenArray ts = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&ts, tsOriginal);

    //printf("Expanding: ");
    TokenArray_Print(&ts);
    //printf("\n");

    struct PPToken* pHead = NULL; //muito facil ter leaks
    while (ts.Size > 0)
    {
        //printf("r = ");
        TokenArray_Print(&r);
        //printf("\n");

        //assert(pHead == NULL);
        pHead =
            TokenArray_PopFront(&ts);

        if (!PPToken_IsIdentifier(pHead))
        {
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; //moved
            continue;
        }

        if (skip_defined &&
            PPToken_IsIdentifier(pHead) &&
            PPToken_IsLexeme(pHead, "defined"))
        {
            struct TokenArray result = TOKENARRAY_INIT;
            GatherDefinedOperator(&ts, macros, &result);
            TokenArray_AppendMove(&r, &result);

            PPToken_Delete(pHead);
            pHead = NULL;

            TokenArray_Destroy(&result);
            continue;
        }

        struct Macro* pMacro = MacroMap_Find(macros, pHead->Lexeme);

        if (pMacro == NULL)
        {
            //if eval mode se nao achar a macro
            //ela vira zero
            if (evalmode)
            {
                Free(pHead->Lexeme);
                pHead->Lexeme = StrDup("0");
                pHead->Token = PPTokenType_Number;
            }
            // Nothing to do if the identifier is not a macro
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; //moved
            continue;
        }

        struct PPToken* pFound =
            TokenSet_Find(&pHead->HiddenSet, pMacro->Name);

        if (pFound)
        {
            // Skip the head token if it is in the hideset
            //printf("Skipping (head is in HS)\n");
            TokenArray_PushBack(&r, pHead);
            pHead = NULL;//moved
            continue;
        }

        struct TokenArray removed_spaces = TOKENARRAY_INIT;

        //printf("replacing for %s tokens=", pMacro->Name);
        TokenArray_Print(&ts);
        //printf("\n");

        if (!pMacro->bIsFunction)
        {
            // Object-like macro
            //printf("Object-like macro\n");

            struct TokenSet hiddenSet = TOKENSET_INIT;
            TokenSetAppendCopy(&hiddenSet, &pHead->HiddenSet);
            TokenSet_PushUnique(&hiddenSet, PPToken_Create(pHead->Lexeme, pHead->Token));

            PPToken_Delete(pHead);
            pHead = NULL; //usado deletado

            struct TokenArray s = TOKENARRAY_INIT;

            SubstituteArgs(pMacro,
                           macros,
                           &pMacro->TokenSequence,
                           NULL, //empty args
                           &hiddenSet,
                           skip_defined,
                           evalmode,
                           caller,
                           &s);

            TokenArray_AppendMove(&s, &ts);
            TokenArray_Swap(&s, &ts);

            TokenArray_Destroy(&s);
            TokenSet_Destroy(&hiddenSet);

            caller = pMacro;
        }

        else if (FillIn(&ts, get_more, &removed_spaces) &&
                 PPToken_IsOpenPar(ts.pItems[0]))
        {
            //printf("Application of a function-like macro\n");

            // struct Map from formal name to value
            struct TokenArrayMap args = TOKENARRAYMAP_INIT;

            PPToken_Delete(TokenArray_PopFront(&ts));

            struct PPToken close = TOKEN_INIT;

            if (!GatherArgs(pHead->Lexeme,
                &ts,
                &pMacro->FormalArguments,
                &args,
                get_more,
                false, /*m.is_vararg,*/
                &close))
            {
                PPToken_Destroy(&close);
                PPToken_Delete(pHead);
                pHead = NULL;//deletado
                continue; // Attempt to bail-out on error
            }


            /*
            After the arguments for the invocation of a function-like
            macro have been identified, argument substitution takes place.
            */

            struct TokenSet hs = TOKENSET_INIT;

            //merge head and close
            SetIntersection(&pHead->HiddenSet,
                            &close.HiddenSet,
                            &hs);
            TokenSet_PushUnique(&hs, PPToken_Create(pMacro->Name, PPTokenType_Identifier));

            PPToken_Delete(pHead);
            pHead = NULL;//deletado

            struct TokenArray s = TOKENARRAY_INIT;

            SubstituteArgs(pMacro,
                           macros,
                           &pMacro->TokenSequence,
                           &args,
                           &hs,
                           skip_defined,
                           evalmode,
                           caller,
                           &s);

            TokenArray_AppendMove(&s, &ts);
            TokenArray_Swap(&s, &ts);
            caller = pMacro;

            TokenSet_Destroy(&hs);
            TokenArray_Destroy(&s);

            TokenArrayMap_Destroy(&args);
            PPToken_Destroy(&close);
        }

        else
        {
            // Function-like macro name lacking a (
            //printf("splicing: [");
            TokenArray_Print(&removed_spaces);
            //printf("]\n");
            TokenArray_AppendMove(&removed_spaces, &ts);
            TokenArray_Swap(&removed_spaces, &ts);
            TokenArray_PushBack(&r, pHead);
            pHead = NULL; //moved
        }

        //TokenArray_Contains(pHead->HiddenSet, pMacro->Name);
        TokenArray_Destroy(&removed_spaces);
    }

    //assert(pHead == NULL);

    TokenArray_Swap(&r, pOutputSequence2);

    TokenArray_Destroy(&r);
    TokenArray_Destroy(&ts);
}


/*
* Try to ensure that ts has at least one non-space token
* Return true if this is the case
* Return any discarded space tokens in removed
*/
bool FillIn(struct TokenArray* ts, bool get_more, struct TokenArray* removed)
{
    while (ts->Size > 0 &&
           PPToken_IsSpace(ts->pItems[0]))
    {
        TokenArray_PushBack(removed, TokenArray_PopFront(ts));
    }

    if (ts->Size > 0)
    {
        return true;
    }

    /*if (get_more)
    {
    Pdtoken t;

    for (;;)
    {
    t.getnext_noexpand();

    if (t.get_code() == EOF)
    return (false);

    else if (t.is_space())
    removed.push_back(t);

    else
    break;
    }

    ts.push_back(t);
    return (true);
    }*/

    return (false);
}




// Paste last of left side with first of right side

void Glue(const struct TokenArray* lsI,
          const struct TokenArray* rsI,
          struct TokenArray* out)
{
    struct TokenArray ls = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&ls, lsI);

    struct TokenArray rs = TOKENARRAY_INIT;
    TokenArray_AppendCopy(&rs, rsI);

    TokenArray_Clear(out);

    if (ls.Size == 0)
    {
        TokenArray_Swap(out, &rs);
    }

    else
    {

        while (ls.Size > 0 &&
               PPToken_IsSpace(ls.pItems[ls.Size - 1]))
        {
            TokenArray_Pop(&ls);
        }

        while (rs.Size > 0 && PPToken_IsSpace(rs.pItems[0]))
        {
            struct PPToken* tk = TokenArray_PopFront(&rs);
            PPToken_Delete(tk);
            tk = NULL;
        }

        if (ls.Size == 0 &&
            rs.Size == 0)
        {
            TokenArray_Swap(out, &ls);
        }

        else
        {
            //Junta o ultimo token do lado esquerdo
            //com o primeiro do lado direito

            struct StrBuilder strNewLexeme = STRBUILDER_INIT;

            if (ls.Size > 0)
            {
                //printf("glue LS: ");
                //printf("%s", ls.pItems[ls.Size - 1]->Lexeme);
                //printf("\n");

                StrBuilder_Append(&strNewLexeme, ls.pItems[ls.Size - 1]->Lexeme);
                TokenArray_Pop(&ls);
            }

            if (rs.Size > 0)
            {
                //printf("glue RS: ");
                //printf("%s", rs.pItems[0]->Lexeme);
                //printf("\n");
                StrBuilder_Append(&strNewLexeme, rs.pItems[0]->Lexeme);
                TokenArray_Pop(&rs);
            }

            //tipo?
            TokenArray_PushBack(&ls, PPToken_Create(strNewLexeme.c_str, PPTokenType_Other));
            StrBuilder_Destroy(&strNewLexeme);

            TokenArray_AppendMove(&ls, &rs);
            TokenArray_Swap(out, &ls);
        }
    }

    //printf("glue returns: ");
    TokenArray_Print(out);
    //printf("\n");

    TokenArray_Destroy(&ls);
    TokenArray_Destroy(&rs);
}

void ExpandMacroToText(const struct TokenArray* pTokenSequence,
                       const struct MacroMap* macros,
                       bool get_more,
                       bool skip_defined,
                       bool evalmode,
                       struct Macro* caller,
                       struct StrBuilder * strBuilder)
{
    StrBuilder_Clear(strBuilder);
    struct TokenArray tks = TOKENARRAY_INIT;
    ExpandMacro(pTokenSequence,
                macros,
                get_more,
                skip_defined,
                evalmode,
                caller,

                &tks);

    for (int i = 0; i < tks.Size; i++)
    {
        if (tks.pItems[i]->Token == PPTokenType_Spaces)
        {
            StrBuilder_Append(strBuilder, " ");
        }
        else
        {
            StrBuilder_Append(strBuilder, tks.pItems[i]->Lexeme);
        }

    }

    TokenArray_Destroy(&tks);
}




int MacroMap_SetAt(struct MacroMap* pMap,
                   const char* Key,
                   struct Macro* newValue)
{
    void* pPrevious;
    int r = Map2_SetAt((struct Map2*)pMap, Key, newValue, &pPrevious);
    Macro_Delete((struct Macro*)pPrevious);
    return r;
}

bool MacroMap_Lookup(const struct MacroMap* pMap,
                     const char* Key,
                     struct Macro** rValue)
{
    return Map2_Lookup((struct Map2*)pMap,
                       Key,
                       (void**)rValue);
}

struct Macro* MacroMap_Find(const struct MacroMap* pMap, const char* Key)
{
    void* p = NULL;
    Map2_Lookup((struct Map2*)pMap,
                Key,
                &p);
    return (struct Macro*)p;
}


bool MacroMap_RemoveKey(struct MacroMap* pMap, const char* Key)
{
    struct Macro* pItem;
    bool r = Map2_RemoveKey((struct Map2*)pMap, Key, (void**)& pItem);

    if (r)
    {
        Macro_Delete(pItem);
    }

    return r;
}

void MacroMap_Init(struct MacroMap* p)
{
    struct MacroMap t = MACROMAP_INIT;
    *p = t;
}

static void Macro_DeleteVoid(void* p)
{
    Macro_Delete((struct Macro*)p);
}

void MacroMap_Destroy(struct MacroMap* p)
{
    Map2_Destroy((struct Map2*)p, Macro_DeleteVoid);
}


void MacroMap_Swap(struct MacroMap* pA, struct MacroMap* pB)
{
    struct MacroMap t = *pA;
    *pA = *pB;
    *pB = t;
}
