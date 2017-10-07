
typedef char *_auto  String;

typedef struct 
{
    String Name;
    int age;
} Person;

void Person_Destroy(Person*  person) _default
{
    free(person->Name);

}

int main()
{
   Person person = _default {0};
   Person_Destroy(&person);
   return 0;
}

