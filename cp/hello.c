
//To compile this code using your compiler
//adds the empty macro _default
//For C' _default is a keyword

typedef char *_auto  String;

typedef struct 
{
    String Name;
    int age;
} Person;

void Person_Destroy(Person*  person) _default;

int main()
{
   Person person = _default {};
   Person_Destroy(&person);
   return 0;
}

