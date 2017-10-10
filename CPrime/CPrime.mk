##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CPrime
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/thiago/Documents/CPrime
ProjectPath            :=C:/Users/thiago/Documents/CPrime/CPrime
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=thiago
Date                   :=09/10/2017
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-32/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-32/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="CPrime.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-32/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-32/bin/ar.exe rcu
CXX      := C:/TDM-GCC-32/bin/g++.exe
CC       := C:/TDM-GCC-32/bin/gcc.exe
CXXFLAGS :=  -g -O0 $(Preprocessors)
CFLAGS   :=  -g -O0 $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-32/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/AllTemplates.c$(ObjectSuffix) $(IntermediateDirectory)/ArrayTemplate.c$(ObjectSuffix) $(IntermediateDirectory)/CodePrint.c$(ObjectSuffix) $(IntermediateDirectory)/CPrime.c$(ObjectSuffix) $(IntermediateDirectory)/ListTemplate.c$(ObjectSuffix) $(IntermediateDirectory)/MapTemplate.c$(ObjectSuffix) $(IntermediateDirectory)/UnionTemplate.c$(ObjectSuffix) $(IntermediateDirectory)/UnitTest.c$(ObjectSuffix) $(IntermediateDirectory)/Array.c$(ObjectSuffix) $(IntermediateDirectory)/Map.c$(ObjectSuffix) \
	$(IntermediateDirectory)/Map2.c$(ObjectSuffix) $(IntermediateDirectory)/Path.c$(ObjectSuffix) $(IntermediateDirectory)/StrBuilder.c$(ObjectSuffix) $(IntermediateDirectory)/Stream.c$(ObjectSuffix) $(IntermediateDirectory)/StringEx.c$(ObjectSuffix) $(IntermediateDirectory)/Ast.c$(ObjectSuffix) $(IntermediateDirectory)/AstPrint.c$(ObjectSuffix) $(IntermediateDirectory)/BasicScanner.c$(ObjectSuffix) $(IntermediateDirectory)/Macro.c$(ObjectSuffix) $(IntermediateDirectory)/Parser.c$(ObjectSuffix) \
	$(IntermediateDirectory)/PPToken.c$(ObjectSuffix) $(IntermediateDirectory)/Scanner.c$(ObjectSuffix) $(IntermediateDirectory)/SymbolMap.c$(ObjectSuffix) $(IntermediateDirectory)/TokenArray.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/AllTemplates.c$(ObjectSuffix): AllTemplates.c $(IntermediateDirectory)/AllTemplates.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/AllTemplates.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AllTemplates.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AllTemplates.c$(DependSuffix): AllTemplates.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AllTemplates.c$(ObjectSuffix) -MF$(IntermediateDirectory)/AllTemplates.c$(DependSuffix) -MM AllTemplates.c

$(IntermediateDirectory)/AllTemplates.c$(PreprocessSuffix): AllTemplates.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AllTemplates.c$(PreprocessSuffix) AllTemplates.c

$(IntermediateDirectory)/ArrayTemplate.c$(ObjectSuffix): ArrayTemplate.c $(IntermediateDirectory)/ArrayTemplate.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/ArrayTemplate.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ArrayTemplate.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ArrayTemplate.c$(DependSuffix): ArrayTemplate.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ArrayTemplate.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ArrayTemplate.c$(DependSuffix) -MM ArrayTemplate.c

$(IntermediateDirectory)/ArrayTemplate.c$(PreprocessSuffix): ArrayTemplate.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ArrayTemplate.c$(PreprocessSuffix) ArrayTemplate.c

$(IntermediateDirectory)/CodePrint.c$(ObjectSuffix): CodePrint.c $(IntermediateDirectory)/CodePrint.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/CodePrint.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CodePrint.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CodePrint.c$(DependSuffix): CodePrint.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CodePrint.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CodePrint.c$(DependSuffix) -MM CodePrint.c

$(IntermediateDirectory)/CodePrint.c$(PreprocessSuffix): CodePrint.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CodePrint.c$(PreprocessSuffix) CodePrint.c

$(IntermediateDirectory)/CPrime.c$(ObjectSuffix): CPrime.c $(IntermediateDirectory)/CPrime.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/CPrime.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPrime.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPrime.c$(DependSuffix): CPrime.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPrime.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CPrime.c$(DependSuffix) -MM CPrime.c

$(IntermediateDirectory)/CPrime.c$(PreprocessSuffix): CPrime.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPrime.c$(PreprocessSuffix) CPrime.c

$(IntermediateDirectory)/ListTemplate.c$(ObjectSuffix): ListTemplate.c $(IntermediateDirectory)/ListTemplate.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/ListTemplate.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ListTemplate.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ListTemplate.c$(DependSuffix): ListTemplate.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ListTemplate.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ListTemplate.c$(DependSuffix) -MM ListTemplate.c

$(IntermediateDirectory)/ListTemplate.c$(PreprocessSuffix): ListTemplate.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ListTemplate.c$(PreprocessSuffix) ListTemplate.c

$(IntermediateDirectory)/MapTemplate.c$(ObjectSuffix): MapTemplate.c $(IntermediateDirectory)/MapTemplate.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/MapTemplate.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MapTemplate.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MapTemplate.c$(DependSuffix): MapTemplate.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MapTemplate.c$(ObjectSuffix) -MF$(IntermediateDirectory)/MapTemplate.c$(DependSuffix) -MM MapTemplate.c

$(IntermediateDirectory)/MapTemplate.c$(PreprocessSuffix): MapTemplate.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MapTemplate.c$(PreprocessSuffix) MapTemplate.c

$(IntermediateDirectory)/UnionTemplate.c$(ObjectSuffix): UnionTemplate.c $(IntermediateDirectory)/UnionTemplate.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/UnionTemplate.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UnionTemplate.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnionTemplate.c$(DependSuffix): UnionTemplate.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UnionTemplate.c$(ObjectSuffix) -MF$(IntermediateDirectory)/UnionTemplate.c$(DependSuffix) -MM UnionTemplate.c

$(IntermediateDirectory)/UnionTemplate.c$(PreprocessSuffix): UnionTemplate.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnionTemplate.c$(PreprocessSuffix) UnionTemplate.c

$(IntermediateDirectory)/UnitTest.c$(ObjectSuffix): UnitTest.c $(IntermediateDirectory)/UnitTest.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/UnitTest.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UnitTest.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnitTest.c$(DependSuffix): UnitTest.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UnitTest.c$(ObjectSuffix) -MF$(IntermediateDirectory)/UnitTest.c$(DependSuffix) -MM UnitTest.c

$(IntermediateDirectory)/UnitTest.c$(PreprocessSuffix): UnitTest.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnitTest.c$(PreprocessSuffix) UnitTest.c

$(IntermediateDirectory)/Array.c$(ObjectSuffix): Array.c $(IntermediateDirectory)/Array.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Array.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Array.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Array.c$(DependSuffix): Array.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Array.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Array.c$(DependSuffix) -MM Array.c

$(IntermediateDirectory)/Array.c$(PreprocessSuffix): Array.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Array.c$(PreprocessSuffix) Array.c

$(IntermediateDirectory)/Map.c$(ObjectSuffix): Map.c $(IntermediateDirectory)/Map.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Map.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Map.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Map.c$(DependSuffix): Map.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Map.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Map.c$(DependSuffix) -MM Map.c

$(IntermediateDirectory)/Map.c$(PreprocessSuffix): Map.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Map.c$(PreprocessSuffix) Map.c

$(IntermediateDirectory)/Map2.c$(ObjectSuffix): Map2.c $(IntermediateDirectory)/Map2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Map2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Map2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Map2.c$(DependSuffix): Map2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Map2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Map2.c$(DependSuffix) -MM Map2.c

$(IntermediateDirectory)/Map2.c$(PreprocessSuffix): Map2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Map2.c$(PreprocessSuffix) Map2.c

$(IntermediateDirectory)/Path.c$(ObjectSuffix): Path.c $(IntermediateDirectory)/Path.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Path.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Path.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Path.c$(DependSuffix): Path.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Path.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Path.c$(DependSuffix) -MM Path.c

$(IntermediateDirectory)/Path.c$(PreprocessSuffix): Path.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Path.c$(PreprocessSuffix) Path.c

$(IntermediateDirectory)/StrBuilder.c$(ObjectSuffix): StrBuilder.c $(IntermediateDirectory)/StrBuilder.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/StrBuilder.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StrBuilder.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StrBuilder.c$(DependSuffix): StrBuilder.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StrBuilder.c$(ObjectSuffix) -MF$(IntermediateDirectory)/StrBuilder.c$(DependSuffix) -MM StrBuilder.c

$(IntermediateDirectory)/StrBuilder.c$(PreprocessSuffix): StrBuilder.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StrBuilder.c$(PreprocessSuffix) StrBuilder.c

$(IntermediateDirectory)/Stream.c$(ObjectSuffix): Stream.c $(IntermediateDirectory)/Stream.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Stream.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stream.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stream.c$(DependSuffix): Stream.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stream.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Stream.c$(DependSuffix) -MM Stream.c

$(IntermediateDirectory)/Stream.c$(PreprocessSuffix): Stream.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stream.c$(PreprocessSuffix) Stream.c

$(IntermediateDirectory)/StringEx.c$(ObjectSuffix): StringEx.c $(IntermediateDirectory)/StringEx.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/StringEx.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StringEx.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StringEx.c$(DependSuffix): StringEx.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StringEx.c$(ObjectSuffix) -MF$(IntermediateDirectory)/StringEx.c$(DependSuffix) -MM StringEx.c

$(IntermediateDirectory)/StringEx.c$(PreprocessSuffix): StringEx.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StringEx.c$(PreprocessSuffix) StringEx.c

$(IntermediateDirectory)/Ast.c$(ObjectSuffix): Ast.c $(IntermediateDirectory)/Ast.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Ast.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Ast.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Ast.c$(DependSuffix): Ast.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Ast.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Ast.c$(DependSuffix) -MM Ast.c

$(IntermediateDirectory)/Ast.c$(PreprocessSuffix): Ast.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Ast.c$(PreprocessSuffix) Ast.c

$(IntermediateDirectory)/AstPrint.c$(ObjectSuffix): AstPrint.c $(IntermediateDirectory)/AstPrint.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/AstPrint.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AstPrint.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AstPrint.c$(DependSuffix): AstPrint.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AstPrint.c$(ObjectSuffix) -MF$(IntermediateDirectory)/AstPrint.c$(DependSuffix) -MM AstPrint.c

$(IntermediateDirectory)/AstPrint.c$(PreprocessSuffix): AstPrint.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AstPrint.c$(PreprocessSuffix) AstPrint.c

$(IntermediateDirectory)/BasicScanner.c$(ObjectSuffix): BasicScanner.c $(IntermediateDirectory)/BasicScanner.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/BasicScanner.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BasicScanner.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BasicScanner.c$(DependSuffix): BasicScanner.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BasicScanner.c$(ObjectSuffix) -MF$(IntermediateDirectory)/BasicScanner.c$(DependSuffix) -MM BasicScanner.c

$(IntermediateDirectory)/BasicScanner.c$(PreprocessSuffix): BasicScanner.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BasicScanner.c$(PreprocessSuffix) BasicScanner.c

$(IntermediateDirectory)/Macro.c$(ObjectSuffix): Macro.c $(IntermediateDirectory)/Macro.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Macro.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Macro.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Macro.c$(DependSuffix): Macro.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Macro.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Macro.c$(DependSuffix) -MM Macro.c

$(IntermediateDirectory)/Macro.c$(PreprocessSuffix): Macro.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Macro.c$(PreprocessSuffix) Macro.c

$(IntermediateDirectory)/Parser.c$(ObjectSuffix): Parser.c $(IntermediateDirectory)/Parser.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Parser.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Parser.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Parser.c$(DependSuffix): Parser.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Parser.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Parser.c$(DependSuffix) -MM Parser.c

$(IntermediateDirectory)/Parser.c$(PreprocessSuffix): Parser.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Parser.c$(PreprocessSuffix) Parser.c

$(IntermediateDirectory)/PPToken.c$(ObjectSuffix): PPToken.c $(IntermediateDirectory)/PPToken.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/PPToken.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PPToken.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PPToken.c$(DependSuffix): PPToken.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PPToken.c$(ObjectSuffix) -MF$(IntermediateDirectory)/PPToken.c$(DependSuffix) -MM PPToken.c

$(IntermediateDirectory)/PPToken.c$(PreprocessSuffix): PPToken.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PPToken.c$(PreprocessSuffix) PPToken.c

$(IntermediateDirectory)/Scanner.c$(ObjectSuffix): Scanner.c $(IntermediateDirectory)/Scanner.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/Scanner.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Scanner.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Scanner.c$(DependSuffix): Scanner.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Scanner.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Scanner.c$(DependSuffix) -MM Scanner.c

$(IntermediateDirectory)/Scanner.c$(PreprocessSuffix): Scanner.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Scanner.c$(PreprocessSuffix) Scanner.c

$(IntermediateDirectory)/SymbolMap.c$(ObjectSuffix): SymbolMap.c $(IntermediateDirectory)/SymbolMap.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/SymbolMap.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SymbolMap.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SymbolMap.c$(DependSuffix): SymbolMap.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SymbolMap.c$(ObjectSuffix) -MF$(IntermediateDirectory)/SymbolMap.c$(DependSuffix) -MM SymbolMap.c

$(IntermediateDirectory)/SymbolMap.c$(PreprocessSuffix): SymbolMap.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SymbolMap.c$(PreprocessSuffix) SymbolMap.c

$(IntermediateDirectory)/TokenArray.c$(ObjectSuffix): TokenArray.c $(IntermediateDirectory)/TokenArray.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/thiago/Documents/CPrime/CPrime/TokenArray.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TokenArray.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TokenArray.c$(DependSuffix): TokenArray.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TokenArray.c$(ObjectSuffix) -MF$(IntermediateDirectory)/TokenArray.c$(DependSuffix) -MM TokenArray.c

$(IntermediateDirectory)/TokenArray.c$(PreprocessSuffix): TokenArray.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TokenArray.c$(PreprocessSuffix) TokenArray.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


