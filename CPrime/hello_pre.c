





















 
 
 
 
 
 
 




 
 
 
 
 
 
 



 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

    


 
 
 
 

    
    


        


            
        
    






 


 



























 
 









 

























 





 
 
 
 
 
 

 
 
 


 
 
 
 


 
 




 


 
 


 


 
 


 
 
 


 
 
 


 







 
 
 

 


 
 



 

 
 

 



 
 




 











 








 

 
 
 

 


























 

 
 
 
 




 
 



 











 










 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






 






 




 
 
 
 






 

































 


















 
 


 




 

 
 
 
 

 



 




 
 


 







 






 




 



 









 









 
 


 
 
 



 




















 
 
 

 
 
 




 
 
 





 
 
 

 








 










 
 
 




 
 
 
 

 
 


 





 


 




 
 
 
 

 
 


 



 


 


 









 

 
 





 





 

 
 





 





 
 



 
 






 
 
 





 





 





 
 



 





 
 
 





 





 





 
 





 
 





 










 






 
 










 
 


















 















 
 
















 



 








 





 





 
 
 
 

 



 
 





 





 





 















 















 
 





 





 





 








 



 
 
 
 

 



 
 





 





 





 















 















 
 





 





 





 







 
 
 




 
 
 


 
 
 

 



 
 





 





 





 





 
 





 





 





 






 


 



 
 





 







 



 
 



 





 



 















 















 
 





 





 





 




 
 


 



 







 







 
 
 
 



















 
 
 
 
 










































 
 
 
 










 
 
 


 
 
 
 

 
 
 
 
 
 

 
 
 











































































 






































































































































































































































































































































































 





 

 














 

 







































    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    
    
    
    

    
    



 
































































































































































































 

































     
    


























 
 
 
 
 

 




 



 
 
 
 








 
 
 
 
 

 
 
 















 




































































































































 










































 
 
 
 
 
 
 
 
 
 














    
    

        typedef unsigned int uintptr_t;
    



    
    

        typedef char* va_list;
    





    











    
    








    

    
    
    


























    





 
 
 








    

    



 




    



















    








        
    



    






        
    









    


 




    
    





    




 




    







    





    



    



      
    


 


 


    typedef unsigned int     size_t;
    typedef int              ptrdiff_t;
    typedef int              intptr_t;





    typedef _Bool __vcrt_bool;


 

    



    



    


 

    
    typedef unsigned short wchar_t;



    


        
    





    





    


 







    


        
    







    
        
    











    void   __security_init_cookie(void);

    
        void   __security_check_cookie(  uintptr_t _StackCookie);
          void   __report_gsfailure(void);
    



extern uintptr_t __security_cookie;


    
    
    


 



 



 
 
 
 
 

    




        
    


 
 

    



    




        
    





    





    





    


 



    














    


        
    





    





    





    




 
 
 
 
 






    typedef _Bool __crt_bool;











    










 
 
 
 
 
 
 
 
 

    


        
    







    




 
 
 
 
 

    










        
    



    



    
        
    




 







 
 
 
 
 



  void   _invalid_parameter_noinfo(void);
    void   _invalid_parameter_noinfo_noreturn(void);

 
  void   _invoke_watson(
      wchar_t const* _Expression,
      wchar_t const* _FunctionName,
      wchar_t const* _FileName,
            unsigned int _LineNo,
            uintptr_t _Reserved);


    


         
         
         
         
         
         
         
         
         
         
         
        
    




 
 
 
 
 







    


        
    




 
 
 
 
 

    






        
    



    


        
    








 
 
 
 
 


















    







    





    


        


            
        
    













    


        
    



    
        
    




    
         
         
        
    




    
        
              
        


    




    
        
    




    
        
    






    




 
 
 
 
 
typedef int                           errno_t;
typedef unsigned short                wint_t;
typedef unsigned short                wctype_t;
typedef long                          __time32_t;
typedef long long                       __time64_t;

typedef struct __crt_locale_data_public
{
      unsigned short const* _locale_pctype;
      int _locale_mb_cur_max;
               unsigned int _locale_lc_codepage;
} __crt_locale_data_public;

typedef struct __crt_locale_pointers
{
    struct __crt_locale_data*    locinfo;
    struct __crt_multibyte_data* mbcinfo;
} __crt_locale_pointers;

typedef __crt_locale_pointers* _locale_t;

typedef struct _Mbstatet
{  
    unsigned long _Wchar;
    unsigned short _Byte, _State;
} _Mbstatet;

typedef _Mbstatet mbstate_t;









    

        typedef __time64_t time_t;
    


 

    



    typedef size_t rsize_t;





 
 
 
 
 

    














        
        
        
        
        
        
        
        
        
        
        
        

    


















































 
 
 
 
 

    







































































        
        
        
        

        

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            


            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

            

        










































    




 

 
 
 
 
 
 
 
 
 




 
 
 
 
 
 
 




 








    



    
        
    







 
 
 
 
 
 
 
 
 
 

    









    






 
 
 




     
     
       
        unsigned long long*   __local_stdio_printf_options(void)
    {
        static unsigned long long _OptionsStorage;
        return &_OptionsStorage;
    }

     
     
       
        unsigned long long*   __local_stdio_scanf_options(void)
    {
        static unsigned long long _OptionsStorage;
        return &_OptionsStorage;
    }























 

 


 
 
 
 
 

    
    typedef struct _iobuf
    {
        void* _Placeholder;
    } FILE;


  FILE*   __acrt_iob_func(unsigned _Ix);










     
     
     
     
     
     
      wint_t   fgetwc(
          FILE* _Stream
        );

     
      wint_t   _fgetwchar(void);

     
      wint_t   fputwc(
             wchar_t _Character,
          FILE*   _Stream);

     
      wint_t   _fputwchar(
          wchar_t _Character
        );

     
      wint_t   getwc(
          FILE* _Stream
        );

     
      wint_t   getwchar(void);


     
     
      wchar_t*   fgetws(
          wchar_t* _Buffer,
                                  int      _BufferCount,
                               FILE*    _Stream
        );

     
      int   fputws(
           wchar_t const* _Buffer,
          FILE*          _Stream
        );

     
     
      wchar_t*   _getws_s(
          wchar_t* _Buffer,
                                  size_t   _BufferCount
        );

     

     
      wint_t   putwc(
             wchar_t _Character,
          FILE*   _Stream
        );

     
      wint_t   putwchar(
          wchar_t _Character
        );

     
      int   _putws(
          wchar_t const* _Buffer
        );

     
      wint_t   ungetwc(
             wint_t _Character,
          FILE*  _Stream
        );

     
      FILE *   _wfdopen(
            int            _FileHandle,
          wchar_t const* _Mode
        );

       
      FILE*   _wfopen(
          wchar_t const* _FileName,
          wchar_t const* _Mode
        );

     
      errno_t   _wfopen_s(
          FILE**         _Stream,
                             wchar_t const* _FileName,
                             wchar_t const* _Mode
        );

     
     
      FILE*   _wfreopen(
           wchar_t const* _FileName,
           wchar_t const* _Mode,
          FILE*          _OldStream
        );

     
      errno_t   _wfreopen_s(
          FILE**         _Stream,
                             wchar_t const* _FileName,
                             wchar_t const* _Mode,
                            FILE*          _OldStream
        );

     
      FILE*   _wfsopen(
          wchar_t const* _FileName,
          wchar_t const* _Mode,
            int            _ShFlag
        );

      void   _wperror(
          wchar_t const* _ErrorMessage
        );

    

         
          FILE*   _wpopen(
              wchar_t const* _Command,
              wchar_t const* _Mode
            );

    

      int   _wremove(
          wchar_t const* _FileName
        );

    
    

     
        wchar_t*   _wtempnam(
          wchar_t const* _Directory,
          wchar_t const* _FilePrefix
        );

    

     
     
      errno_t   _wtmpnam_s(
          wchar_t* _Buffer,
                                  size_t   _BufferCount
        );

     

        
  
 wchar_t*    _wtmpnam( 
      wchar_t *  _Buffer
 );



     
     
     
     
     
     
      wint_t   _fgetwc_nolock(
          FILE* _Stream
        );

     
      wint_t   _fputwc_nolock(
             wchar_t _Character,
          FILE*   _Stream
        );

     
      wint_t   _getwc_nolock(
          FILE* _Stream
        );

     
      wint_t   _putwc_nolock(
             wchar_t _Character,
          FILE*   _Stream
        );

     
      wint_t   _ungetwc_nolock(
             wint_t _Character,
          FILE*  _Stream
        );

    







     
    




     
     
     
     
     
     
      int   __stdio_common_vfwprintf(
                                             unsigned long long _Options,
                                          FILE*            _Stream,
            wchar_t const*   _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
      int   __stdio_common_vfwprintf_s(
                                             unsigned long long _Options,
                                          FILE*            _Stream,
            wchar_t const*   _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
      int   __stdio_common_vfwprintf_p(
                                             unsigned long long _Options,
                                          FILE*            _Stream,
            wchar_t const*   _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
      int   _vfwprintf_l(
                                          FILE*          const _Stream,
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        return __stdio_common_vfwprintf((*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);
    }
    

     
      int   vfwprintf(
                                FILE*          const _Stream,
            wchar_t const* const _Format,
                                      va_list              _ArgList
        )
    

    {
        return _vfwprintf_l(_Stream, _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vfwprintf_s_l(
                                          FILE*          const _Stream,
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        return __stdio_common_vfwprintf_s((*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);
    }
    

    

         
          int   vfwprintf_s(
                                    FILE*          const _Stream,
                wchar_t const* const _Format,
                                          va_list              _ArgList
            )
    

        {
            return _vfwprintf_s_l(_Stream, _Format, ((void *)0), _ArgList);
        }
    

    

     
      int   _vfwprintf_p_l(
                                          FILE*          const _Stream,
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        return __stdio_common_vfwprintf_p((*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);
    }
    

     
      int   _vfwprintf_p(
                                FILE*          const _Stream,
            wchar_t const* const _Format,
                                      va_list              _ArgList
        )
    

    {
        return _vfwprintf_p_l(_Stream, _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vwprintf_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        return _vfwprintf_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    }
    

     
      int   vwprintf(
            wchar_t const* const _Format,
                                      va_list              _ArgList
        )
    

    {
        return _vfwprintf_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vwprintf_s_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        return _vfwprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    }
    

    

         
          int   vwprintf_s(
                wchar_t const* const _Format,
                                          va_list              _ArgList
            )
    

        {
            return _vfwprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
        }
    

    

     
      int   _vwprintf_p_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        return _vfwprintf_p_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    }
    

     
      int   _vwprintf_p(
            wchar_t const* const _Format,
                                      va_list              _ArgList
        )
    

    {
        return _vfwprintf_p_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
    }
    

     
      int   _fwprintf_l(
                                          FILE*          const _Stream,
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   fwprintf(
                                FILE*          const _Stream,
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_l(_Stream, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _fwprintf_s_l(
                                          FILE*          const _Stream,
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_s_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   fwprintf_s(
                                    FILE*          const _Stream,
                wchar_t const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vfwprintf_s_l(_Stream, _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

     
      int   _fwprintf_p_l(
                                          FILE*          const _Stream,
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_p_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _fwprintf_p(
                                FILE*          const _Stream,
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_p_l(_Stream, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _wprintf_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   wprintf(
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _wprintf_s_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   wprintf_s(
                wchar_t const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vfwprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

     
      int   _wprintf_p_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_p_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _wprintf_p(
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwprintf_p_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    


     
     
     
     
     
     
      int   __stdio_common_vfwscanf(
                                            unsigned long long _Options,
                                         FILE*            _Stream,
            wchar_t const*   _Format,
                                        _locale_t        _Locale,
                                               va_list          _ArgList
        );

     
      int   _vfwscanf_l(
          FILE*                                const _Stream,
            wchar_t const* const _Format,
                               _locale_t      const _Locale,
                                      va_list              _ArgList
        )
    

    {
        return __stdio_common_vfwscanf(
            (*__local_stdio_scanf_options ()),
            _Stream, _Format, _Locale, _ArgList);
    }
    

     
      int   vfwscanf(
          FILE*                                const _Stream,
            wchar_t const* const _Format,
                                      va_list              _ArgList
        )
    

    {
        return _vfwscanf_l(_Stream, _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vfwscanf_s_l(
                                FILE*          const _Stream,
            wchar_t const* const _Format,
                               _locale_t      const _Locale,
                                      va_list              _ArgList
        )
    

    {
        return __stdio_common_vfwscanf(
            (*__local_stdio_scanf_options ()) | (1ULL << 0),
            _Stream, _Format, _Locale, _ArgList);
    }
    

    

         
          int   vfwscanf_s(
                                    FILE*          const _Stream,
                wchar_t const* const _Format,
                                          va_list              _ArgList
            )
    

        {
            return _vfwscanf_s_l(_Stream, _Format, ((void *)0), _ArgList);
        }
    

    

      int   _vwscanf_l(
            wchar_t const* const _Format,
                               _locale_t      const _Locale,
                                      va_list              _ArgList
        )
    

    {
        return _vfwscanf_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
    }
    

     
      int   vwscanf(
            wchar_t const* const _Format,
                                      va_list              _ArgList
        )
    

    {
        return _vfwscanf_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vwscanf_s_l(
            wchar_t const* const _Format,
                               _locale_t      const _Locale,
                                      va_list              _ArgList
        )
    

    {
        return _vfwscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
    }
    

    

         
          int   vwscanf_s(
                wchar_t const* const _Format,
                                          va_list              _ArgList
            )
    

        {
            return _vfwscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
        }
    

    

       
      int   _fwscanf_l(
                                         FILE*          const _Stream,
            wchar_t const* const _Format,
                                        _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwscanf_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

       
      int   fwscanf(
                               FILE*          const _Stream,
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwscanf_l(_Stream, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _fwscanf_s_l(
                                           FILE*          const _Stream,
            wchar_t const* const _Format,
                                          _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwscanf_s_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   fwscanf_s(
                                     FILE*          const _Stream,
                wchar_t const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vfwscanf_s_l(_Stream, _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

       
      int   _wscanf_l(
            wchar_t const* const _Format,
                                        _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwscanf_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

       
      int   wscanf(
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwscanf_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _wscanf_s_l(
            wchar_t const* const _Format,
                                          _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfwscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   wscanf_s(
                wchar_t const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vfwscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    



     
     
     
     
     
    
        
    



     
     
      int   __stdio_common_vswprintf(
                                             unsigned long long _Options,
                 wchar_t*         _Buffer,
                                             size_t           _BufferCount,
            wchar_t const*   _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
     
      int   __stdio_common_vswprintf_s(
                                             unsigned long long _Options,
                     wchar_t*         _Buffer,
                                             size_t           _BufferCount,
            wchar_t const*   _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
     
      int   __stdio_common_vsnwprintf_s(
                                             unsigned long long _Options,
                 wchar_t*         _Buffer,
                                             size_t           _BufferCount,
                                             size_t           _MaxCount,
            wchar_t const*   _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
     
      int   __stdio_common_vswprintf_p(
                                             unsigned long long _Options,
                     wchar_t*         _Buffer,
                                             size_t           _BufferCount,
            wchar_t const*   _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
       
      int   _vsnwprintf_l(
            wchar_t*       const _Buffer,
                                                  size_t         const _BufferCount,
                 wchar_t const* const _Format,
                                              _locale_t      const _Locale,
                                                     va_list              _ArgList
        )
    

    {
        int const _Result = __stdio_common_vswprintf(
            (*__local_stdio_printf_options()) | (1ULL << 0),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

    
    

     
     
      int   _vsnwprintf_s_l(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                                       size_t         const _MaxCount,
                      wchar_t const* const _Format,
                                                   _locale_t      const _Locale,
                                                          va_list              _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsnwprintf_s(
            (*__local_stdio_printf_options()),
            _Buffer, _BufferCount, _MaxCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vsnwprintf_s(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                                       size_t         const _MaxCount,
                                wchar_t const* const _Format,
                                                          va_list              _ArgList
        )
    

    {
        return _vsnwprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, ((void *)0), _ArgList);
    }
    

       
  
 int    _snwprintf(
      wchar_t * _Buffer, 
   size_t  _BufferCount, 
     wchar_t const*  _Format
 , ...);     
  
 int    _vsnwprintf(
      wchar_t * _Buffer, 
   size_t  _BufferCount, 
     wchar_t const*  _Format
 , va_list _Args);

    

     
       
      int   _vsnwprintf(
            wchar_t*       _Buffer,
                                                  size_t         _BufferCount,
                           wchar_t const* _Format,
                                                     va_list        _ArgList
        )
    

    {
        
        
        return _vsnwprintf_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        
    }
    

     

     
     
      int   _vswprintf_c_l(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                      wchar_t const* const _Format,
                                                   _locale_t      const _Locale,
                                                          va_list              _ArgList
        )
    

    {
        int const _Result = __stdio_common_vswprintf(
            (*__local_stdio_printf_options()),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vswprintf_c(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                wchar_t const* const _Format,
                                                          va_list              _ArgList
        )
    

    {
        return _vswprintf_c_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
    }
    

     
     
      int   _vswprintf_l(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                      wchar_t const* const _Format,
                                                   _locale_t      const _Locale,
                                                          va_list              _ArgList
        )
    

    {
        
        
        return _vswprintf_c_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        
    }
    

     
     
      int   __vswprintf_l(
                   wchar_t*       const _Buffer,
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        return _vswprintf_l(_Buffer, (size_t)-1, _Format, _Locale, _ArgList);
    }
    

     
     
      int   _vswprintf(
            wchar_t*       const _Buffer,
               wchar_t const* const _Format,
                                         va_list              _ArgList
        )
    

    {
        return _vswprintf_l(_Buffer, (size_t)-1, _Format, ((void *)0), _ArgList);
    }
    

     
     
      int   vswprintf(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                      wchar_t const* const _Format,
                                                          va_list              _ArgList
        )
    

    {
        return _vswprintf_c_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
    }
    

     
     
      int   _vswprintf_s_l(
            wchar_t*       const _Buffer,
                                                   size_t         const _BufferCount,
                  wchar_t const* const _Format,
                                               _locale_t      const _Locale,
                                                      va_list              _ArgList
        )
    

    {
        int const _Result = __stdio_common_vswprintf_s(
            (*__local_stdio_printf_options()),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

    

         
          int   vswprintf_s(
                wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                wchar_t const* const _Format,
                                                          va_list              _ArgList
            )
    

        {
            return _vswprintf_s_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        }
    

    

     

     
     
      int   _vswprintf_p_l(
            wchar_t*       const _Buffer,
                                                   size_t         const _BufferCount,
                  wchar_t const* const _Format,
                                               _locale_t      const _Locale,
                                                      va_list              _ArgList
        )
    

    {
        int const _Result = __stdio_common_vswprintf_p(
            (*__local_stdio_printf_options()),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vswprintf_p(
            wchar_t*       const _Buffer,
                                                   size_t         const _BufferCount,
                            wchar_t const* const _Format,
                                                      va_list              _ArgList
        )
    

    {
        return _vswprintf_p_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
    }
    

     
     
      int   _vscwprintf_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        int const _Result = __stdio_common_vswprintf(
            (*__local_stdio_printf_options()) | (1ULL << 1),
            ((void *)0), 0, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vscwprintf(
            wchar_t const* const _Format,
                                      va_list              _ArgList
        )
    

    {
        return _vscwprintf_l(_Format, ((void *)0), _ArgList);
    }
    

     
     
      int   _vscwprintf_p_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
                                                va_list              _ArgList
        )
    

    {
        int const _Result = __stdio_common_vswprintf_p(
            (*__local_stdio_printf_options()) | (1ULL << 1),
            ((void *)0), 0, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vscwprintf_p(
            wchar_t const* const _Format,
                                      va_list              _ArgList
        )
    

    {
        return _vscwprintf_p_l(_Format, ((void *)0), _ArgList);
    }
    

     
     
      int   __swprintf_l(
                   wchar_t*       const _Buffer,
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = __vswprintf_l(_Buffer, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _swprintf_l(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                      wchar_t const* const _Format,
                                                   _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswprintf_c_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _swprintf(
            wchar_t*       const _Buffer,
               wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = __vswprintf_l(_Buffer, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   swprintf(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswprintf_c_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    
     
     
    

       
  
 int    __swprintf_l(
     wchar_t * _Buffer, 
     wchar_t const*  _Format, 
   _locale_t  _Locale
 , ...);     
  
 int    __vswprintf_l(
     wchar_t * _Buffer, 
     wchar_t const*  _Format, 
   _locale_t  _Locale
 , va_list _Args);

       
  
 int    _swprintf(
     wchar_t * _Buffer, 
     wchar_t const*  _Format
 , ...);     
  
 int    _vswprintf(
     wchar_t * _Buffer, 
     wchar_t const*  _Format
 , va_list _Args);

    

     
     
      int   _swprintf_s_l(
            wchar_t*       const _Buffer,
                                                   size_t         const _BufferCount,
                  wchar_t const* const _Format,
                                               _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswprintf_s_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   swprintf_s(
                wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                wchar_t const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vswprintf_s_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

     

     
     
      int   _swprintf_p_l(
            wchar_t*       const _Buffer,
                                                   size_t         const _BufferCount,
                  wchar_t const* const _Format,
                                               _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswprintf_p_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _swprintf_p(
            wchar_t*       const _Buffer,
                                                   size_t         const _BufferCount,
                            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswprintf_p_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _swprintf_c_l(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                      wchar_t const* const _Format,
                                                   _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswprintf_c_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _swprintf_c(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswprintf_c_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
       
      int   _snwprintf_l(
            wchar_t*       const _Buffer,
                                                  size_t         const _BufferCount,
                 wchar_t const* const _Format,
                                              _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        
        
        _Result = _vsnwprintf_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _snwprintf(
            wchar_t*       _Buffer,
                                                  size_t         _BufferCount,
                           wchar_t const* _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        
        
        _Result = _vsnwprintf_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _snwprintf_s_l(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                                       size_t         const _MaxCount,
                      wchar_t const* const _Format,
                                                   _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsnwprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _snwprintf_s(
            wchar_t*       const _Buffer,
                                                       size_t         const _BufferCount,
                                                       size_t         const _MaxCount,
                                wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsnwprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     

     
      int   _scwprintf_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vscwprintf_l(_Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _scwprintf(
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vscwprintf_l(_Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _scwprintf_p_l(
            wchar_t const* const _Format,
                                         _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vscwprintf_p_l(_Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _scwprintf_p(
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vscwprintf_p_l(_Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    


    
        
        

        


        
    

    







     
     
     
     
     
     
      int   __stdio_common_vswscanf(
                                            unsigned long long _Options,
                  wchar_t const*   _Buffer,
                                            size_t           _BufferCount,
            wchar_t const*   _Format,
                                        _locale_t        _Locale,
                                               va_list          _ArgList
        );

     
     
      int   _vswscanf_l(
                                 wchar_t const* const _Buffer,
            wchar_t const* const _Format,
                               _locale_t      const _Locale,
                                      va_list              _ArgList
        )
    

    {
        return __stdio_common_vswscanf(
            (*__local_stdio_scanf_options ()),
            _Buffer, (size_t)-1, _Format, _Locale, _ArgList);
    }
    

     
     
      int   vswscanf(
                                 wchar_t const* _Buffer,
            wchar_t const* _Format,
                                      va_list        _ArgList
        )
    

    {
        return _vswscanf_l(_Buffer, _Format, ((void *)0), _ArgList);
    }
    

     
     
      int   _vswscanf_s_l(
                                 wchar_t const* const _Buffer,
            wchar_t const* const _Format,
                               _locale_t      const _Locale,
                                      va_list              _ArgList
        )
    

    {
        return __stdio_common_vswscanf(
            (*__local_stdio_scanf_options ()) | (1ULL << 0),
            _Buffer, (size_t)-1, _Format, _Locale, _ArgList);
    }
    

    

         
         
          int   vswscanf_s(
                                     wchar_t const* const _Buffer,
                wchar_t const* const _Format,
                                          va_list              _ArgList
            )
    

        {
            return _vswscanf_s_l(_Buffer, _Format, ((void *)0), _ArgList);
        }
    

    

     

     
       
      int   _vsnwscanf_l(
                  wchar_t const* const _Buffer,
                                            size_t         const _BufferCount,
            wchar_t const* const _Format,
                                        _locale_t      const _Locale,
                                               va_list              _ArgList
        )
    

    {
        return __stdio_common_vswscanf(
            (*__local_stdio_scanf_options ()),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);
    }
    

     
     
      int   _vsnwscanf_s_l(
                    wchar_t const* const _Buffer,
                                              size_t         const _BufferCount,
            wchar_t const* const _Format,
                                          _locale_t      const _Locale,
                                                 va_list              _ArgList
        )
    

    {
        return __stdio_common_vswscanf(
            (*__local_stdio_scanf_options ()) | (1ULL << 0),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);
    }
    

     
       
      int   _swscanf_l(
                                          wchar_t const* const _Buffer,
            wchar_t const* const _Format,
                                        _locale_t            _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswscanf_l(_Buffer, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
       
      int   swscanf(
                                wchar_t const* const _Buffer,
            wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswscanf_l(_Buffer, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _swscanf_s_l(
                                            wchar_t const* const _Buffer,
            wchar_t const* const _Format,
                                          _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vswscanf_s_l(_Buffer, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
         
          int   swscanf_s(
                                      wchar_t const* const _Buffer,
                wchar_t const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vswscanf_s_l(_Buffer, _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

     
       
      int   _snwscanf_l(
                  wchar_t const* const _Buffer,
                                            size_t         const _BufferCount,
            wchar_t const* const _Format,
                                        _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        
        
        _Result = _vsnwscanf_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
       
      int   _snwscanf(
            wchar_t const* const _Buffer,
                                      size_t         const _BufferCount,
                wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        
        
        _Result = _vsnwscanf_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _snwscanf_s_l(
                    wchar_t const* const _Buffer,
                                              size_t         const _BufferCount,
            wchar_t const* const _Format,
                                          _locale_t      const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsnwscanf_s_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _snwscanf_s(
             wchar_t const* const _Buffer,
                                       size_t         const _BufferCount,
               wchar_t const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsnwscanf_s_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    





 

 

 





 




 












    




 











    
    



typedef long long fpos_t;





     
      errno_t   _get_stream_buffer_pointers(
               FILE*   _Stream,
          char*** _Base,
          char*** _Pointer,
          int**   _Count
        );


     
     
     
     
     
    

         
          errno_t   clearerr_s(
              FILE* _Stream
            );

         
          errno_t   fopen_s(
              FILE**      _Stream,
                                 char const* _FileName,
                                 char const* _Mode
            );

         
         
          size_t   fread_s(
                void*  _Buffer,
                                    size_t _BufferSize,
                                                                            size_t _ElementSize,
                                                                            size_t _ElementCount,
                                                                         FILE*  _Stream
            );

         
          errno_t   freopen_s(
              FILE**      _Stream,
                                 char const* _FileName,
                                 char const* _Mode,
                                FILE*       _OldStream
            );

         
          char*   gets_s(
              char*   _Buffer,
                               rsize_t _Size
            );

         
          errno_t   tmpfile_s(
                FILE** _Stream
            );

         
         
          errno_t   tmpnam_s(
              char*   _Buffer,
                               rsize_t _Size
            );

    

      void   clearerr(
          FILE* _Stream
        );

     
     
      int   fclose(
          FILE* _Stream
        );

     
      int   _fcloseall(void);

     
      FILE*   _fdopen(
            int         _FileHandle,
          char const* _Mode
        );

     
      int   feof(
          FILE* _Stream
        );

     
      int   ferror(
          FILE* _Stream
        );

     
      int   fflush(
          FILE* _Stream
        );

     
     
      int   fgetc(
          FILE* _Stream
        );

     
      int   _fgetchar(void);

     
     
      int   fgetpos(
          FILE*   _Stream,
            fpos_t* _Position
        );

     
     
      char*   fgets(
          char* _Buffer,
                               int   _MaxCount,
                            FILE* _Stream
        );

     
      int   _fileno(
          FILE* _Stream
        );

     
      int   _flushall(void);

       
      FILE*   fopen(
          char const* _FileName,
          char const* _Mode
        );


     
     
      int   fputc(
             int   _Character,
          FILE* _Stream
        );

     
      int   _fputchar(
          int _Character
        );

     
     
      int   fputs(
           char const* _Buffer,
          FILE*       _Stream
        );

     
      size_t   fread(
          void*  _Buffer,
                                                      size_t _ElementSize,
                                                      size_t _ElementCount,
                                                   FILE*  _Stream
        );

     
       
      FILE*   freopen(
           char const* _FileName,
           char const* _Mode,
          FILE*       _Stream
        );

     
      FILE*   _fsopen(
          char const* _FileName,
          char const* _Mode,
            int         _ShFlag
        );

     
     
      int   fsetpos(
          FILE*         _Stream,
             fpos_t const* _Position
        );

     
     
      int   fseek(
          FILE* _Stream,
             long  _Offset,
             int   _Origin
        );

     
     
      int   _fseeki64(
          FILE*   _Stream,
             long long _Offset,
             int     _Origin
        );

     
     
      long   ftell(
          FILE* _Stream
        );

     
     
      long long   _ftelli64(
          FILE* _Stream
        );

     
      size_t   fwrite(
          void const* _Buffer,
                                                    size_t      _ElementSize,
                                                    size_t      _ElementCount,
                                                 FILE*       _Stream
        );

     
     
      int   getc(
          FILE* _Stream
        );

     
      int   getchar(void);

     
      int   _getmaxstdio(void);

     

     
      int   _getw(
          FILE* _Stream
        );

      void   perror(
          char const* _ErrorMessage
        );

    

         
         
          int   _pclose(
              FILE* _Stream
            );

         
          FILE*   _popen(
              char const* _Command,
              char const* _Mode
            );

    

     
     
      int   putc(
             int   _Character,
          FILE* _Stream
        );

     
      int   putchar(
          int _Character
        );

     
      int   puts(
          char const* _Buffer
        );

     
     
      int   _putw(
             int   _Word,
          FILE* _Stream
        );

      int   remove(
          char const* _FileName
        );

     
      int   rename(
          char const* _OldFileName,
          char const* _NewFileName
        );

      int   _unlink(
          char const* _FileName
        );

    

         
          int   unlink(
              char const* _FileName
            );

    

      void   rewind(
          FILE* _Stream
        );

     
      int   _rmtmp(void);

     
      void   setbuf(
                                                      FILE* _Stream,
            char* _Buffer
        );

     
      int   _setmaxstdio(
          int _Maximum
        );

     
     
      int   setvbuf(
                               FILE*  _Stream,
            char*  _Buffer,
                                  int    _Mode,
                                  size_t _Size
        );

    


     
        char*   _tempnam(
          char const* _DirectoryName,
          char const* _FilePrefix
        );

    


       
      FILE*   tmpfile(void);

     



    
  
 char*    tmpnam( 
      char *  _Buffer
 );


     
     
      int   ungetc(
             int   _Character,
          FILE* _Stream
        );



     
     
     
     
     
      void   _lock_file(
          FILE* _Stream
        );

      void   _unlock_file(
          FILE* _Stream
        );

     
     
      int   _fclose_nolock(
          FILE* _Stream
        );

     
     
      int   _fflush_nolock(
          FILE* _Stream
        );

     
     
      int   _fgetc_nolock(
          FILE* _Stream
        );

     
     
      int   _fputc_nolock(
             int   _Character,
          FILE* _Stream
        );

     
      size_t   _fread_nolock(
          void*  _Buffer,
                                                      size_t _ElementSize,
                                                      size_t _ElementCount,
                                                   FILE*  _Stream
        );

     
     
      size_t   _fread_nolock_s(
          void*  _Buffer,
                              size_t _BufferSize,
                                                                      size_t _ElementSize,
                                                                      size_t _ElementCount,
                                                                   FILE*  _Stream
        );

     
      int   _fseek_nolock(
          FILE* _Stream,
             long  _Offset,
             int   _Origin
        );

     
      int   _fseeki64_nolock(
          FILE*   _Stream,
             long long _Offset,
             int     _Origin
        );

     
      long   _ftell_nolock(
          FILE* _Stream
        );

     
      long long   _ftelli64_nolock(
          FILE* _Stream
        );

     
      size_t   _fwrite_nolock(
          void const* _Buffer,
                                                    size_t      _ElementSize,
                                                    size_t      _ElementCount,
                                                 FILE*       _Stream
        );

     
      int   _getc_nolock(
          FILE* _Stream
        );

     
      int   _putc_nolock(
             int   _Character,
          FILE* _Stream
        );

     
      int   _ungetc_nolock(
             int   _Character,
          FILE* _Stream
        );

    
    
    
    



    

















      int*   __p__commode(void);

    

        
    



     
    


     
     
     
     
     
      int   __stdio_common_vfprintf(
                                             unsigned long long _Options,
                                          FILE*            _Stream,
            char const*      _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

      int   __stdio_common_vfprintf_s(
                                             unsigned long long _Options,
                                          FILE*            _Stream,
            char const*      _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
      int   __stdio_common_vfprintf_p(
                                             unsigned long long _Options,
                                          FILE*            _Stream,
            char const*      _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
      int   _vfprintf_l(
           FILE*       const _Stream,
            char const* const _Format,
          _locale_t   const _Locale,
                 va_list           _ArgList
        )
    

    {
        return __stdio_common_vfprintf((*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);
    }
    

     
      int   vfprintf(
                                FILE*       const _Stream,
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vfprintf_l(_Stream, _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vfprintf_s_l(
           FILE*       const _Stream,
            char const* const _Format,
          _locale_t   const _Locale,
                 va_list           _ArgList
        )
    

    {
        return __stdio_common_vfprintf_s((*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);
    }
    

    

         
          int   vfprintf_s(
                                    FILE*       const _Stream,
                char const* const _Format,
                                          va_list           _ArgList
            )
    

        {
            return _vfprintf_s_l(_Stream, _Format, ((void *)0), _ArgList);
        }
    

    

     
      int   _vfprintf_p_l(
           FILE*       const _Stream,
            char const* const _Format,
          _locale_t   const _Locale,
                 va_list           _ArgList
        )
    

    {
        return __stdio_common_vfprintf_p((*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);
    }
    

     
      int   _vfprintf_p(
                                FILE*       const _Stream,
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vfprintf_p_l(_Stream, _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vprintf_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
                                                va_list           _ArgList
        )
    

    {
        return _vfprintf_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    }
    

     
      int   vprintf(
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vfprintf_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vprintf_s_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
                                                va_list           _ArgList
        )
    

    {
        return _vfprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    }
    

    

         
          int   vprintf_s(
                char const* const _Format,
                                          va_list           _ArgList
            )
    

        {
            return _vfprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
        }
    

    

     
      int   _vprintf_p_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
                                                va_list           _ArgList
        )
    

    {
        return _vfprintf_p_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    }
    

     
      int   _vprintf_p(
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vfprintf_p_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
    }
    

     
      int   _fprintf_l(
                                          FILE*       const _Stream,
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   fprintf(
                                FILE*       const _Stream,
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_l(_Stream, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

      int   _set_printf_count_output(
          int _Value
        );

      int   _get_printf_count_output(void);

     
      int   _fprintf_s_l(
                                          FILE*       const _Stream,
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_s_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   fprintf_s(
                                    FILE*       const _Stream,
                char const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vfprintf_s_l(_Stream, _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

     
      int   _fprintf_p_l(
                                          FILE*       const _Stream,
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_p_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _fprintf_p(
                                FILE*       const _Stream,
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_p_l(_Stream, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _printf_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   printf(
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _printf_s_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   printf_s(
                char const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vfprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

     
      int   _printf_p_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_p_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _printf_p(
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfprintf_p_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    


     
     
     
     
     
      int   __stdio_common_vfscanf(
                                            unsigned long long _Options,
                                         FILE*            _Stream,
            char const*      _Format,
                                        _locale_t        _Locale,
                                               va_list          _Arglist
        );

     
      int   _vfscanf_l(
                                FILE*       const _Stream,
            char const* const _Format,
                               _locale_t   const _Locale,
                                      va_list           _ArgList
        )
    

    {
        return __stdio_common_vfscanf(
            (*__local_stdio_scanf_options ()),
            _Stream, _Format, _Locale, _ArgList);
    }
    

     
      int   vfscanf(
                                FILE*       const _Stream,
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vfscanf_l(_Stream, _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vfscanf_s_l(
                                FILE*       const _Stream,
            char const* const _Format,
                               _locale_t   const _Locale,
                                      va_list           _ArgList
        )
    

    {
        return __stdio_common_vfscanf(
            (*__local_stdio_scanf_options ()) | (1ULL << 0),
            _Stream, _Format, _Locale, _ArgList);
    }
    


    

         
          int   vfscanf_s(
                                    FILE*       const _Stream,
                char const* const _Format,
                                          va_list           _ArgList
            )
    

        {
            return _vfscanf_s_l(_Stream, _Format, ((void *)0), _ArgList);
        }
    

    

     
      int   _vscanf_l(
            char const* const _Format,
                               _locale_t   const _Locale,
                                      va_list           _ArgList
        )
    

    {
        return _vfscanf_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
    }
    

     
      int   vscanf(
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vfscanf_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vscanf_s_l(
            char const* const _Format,
                               _locale_t   const _Locale,
                                      va_list           _ArgList
        )
    

    {
        return _vfscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
    }
    

    

         
          int   vscanf_s(
                char const* const _Format,
                                          va_list           _ArgList
            )
    

        {
            return _vfscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
        }
    

    

       
      int   _fscanf_l(
                                         FILE*       const _Stream,
            char const* const _Format,
                                        _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfscanf_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

       
      int   fscanf(
                               FILE*       const _Stream,
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfscanf_l(_Stream, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _fscanf_s_l(
                                           FILE*       const _Stream,
            char const* const _Format,
                                          _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfscanf_s_l(_Stream, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   fscanf_s(
                                     FILE*       const _Stream,
                char const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vfscanf_s_l(_Stream, _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

       
      int   _scanf_l(
            char const* const _Format,
                                        _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfscanf_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

       
      int   scanf(
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfscanf_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _scanf_s_l(
            char const* const _Format,
                                          _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vfscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   scanf_s(
                char const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vfscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    



     
     
     
     
     
     
      int   __stdio_common_vsprintf(
                                             unsigned long long _Options,
                 char*            _Buffer,
                                             size_t           _BufferCount,
            char const*      _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
      int   __stdio_common_vsprintf_s(
                                             unsigned long long _Options,
                     char*            _Buffer,
                                             size_t           _BufferCount,
            char const*      _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
      int   __stdio_common_vsnprintf_s(
                                             unsigned long long _Options,
                 char*            _Buffer,
                                             size_t           _BufferCount,
                                             size_t           _MaxCount,
            char const*      _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
      int   __stdio_common_vsprintf_p(
                                             unsigned long long _Options,
                     char*            _Buffer,
                                             size_t           _BufferCount,
            char const*      _Format,
                                         _locale_t        _Locale,
                                                va_list          _ArgList
        );

     
       
      int   _vsnprintf_l(
            char*       const _Buffer,
                                                  size_t      const _BufferCount,
                 char const* const _Format,
                                              _locale_t   const _Locale,
                                                     va_list           _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsprintf(
            (*__local_stdio_printf_options()) | (1ULL << 0),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vsnprintf(
            char*       const _Buffer,
                                                 size_t      const _BufferCount,
                          char const* const _Format,
                                                    va_list           _ArgList
        )
    

    {
        
        
        return _vsnprintf_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        
    }
    

    



     
     
      int   vsnprintf(
            char*       const _Buffer,
                                                       size_t      const _BufferCount,
                                char const* const _Format,
                                                          va_list           _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsprintf(
            (*__local_stdio_printf_options()) | (1ULL << 1),
            _Buffer, _BufferCount, _Format, ((void *)0), _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
       
      int   _vsprintf_l(
            char*       const _Buffer,
                                    char const* const _Format,
                                  _locale_t   const _Locale,
                                         va_list           _ArgList
        )
    

    {
        
        
        return _vsnprintf_l(_Buffer, (size_t)-1, _Format, _Locale, _ArgList);
        
    }
    

     
       
      int   vsprintf(
            char*       const _Buffer,
               char const* const _Format,
                                         va_list           _ArgList
        )
    

    {
        
        
        return _vsnprintf_l(_Buffer, (size_t)-1, _Format, ((void *)0), _ArgList);
        
    }
    

     
     
      int   _vsprintf_s_l(
            char*       const _Buffer,
                                                   size_t      const _BufferCount,
                  char const* const _Format,
                                               _locale_t   const _Locale,
                                                      va_list           _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsprintf_s(
            (*__local_stdio_printf_options()),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

    

         
         
          int   vsprintf_s(
                char*       const _Buffer,
                                                       size_t      const _BufferCount,
                                char const* const _Format,
                                                          va_list           _ArgList
            )
    

        {
            return _vsprintf_s_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        }
    

         

    

     
     
      int   _vsprintf_p_l(
            char*       const _Buffer,
                                                   size_t      const _BufferCount,
                  char const* const _Format,
                                               _locale_t   const _Locale,
                                                      va_list           _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsprintf_p(
            (*__local_stdio_printf_options()),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vsprintf_p(
            char*       const _Buffer,
                                                   size_t      const _BufferCount,
                            char const* const _Format,
                                                      va_list           _ArgList
        )
    

    {
        return _vsprintf_p_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
    }
    

     
     
      int   _vsnprintf_s_l(
            char*       const _Buffer,
                                                       size_t      const _BufferCount,
                                                       size_t      const _MaxCount,
                      char const* const _Format,
                                                   _locale_t   const _Locale,
                                                          va_list          _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsnprintf_s(
            (*__local_stdio_printf_options()),
            _Buffer, _BufferCount, _MaxCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vsnprintf_s(
            char*       const _Buffer,
                                                       size_t      const _BufferCount,
                                                       size_t      const _MaxCount,
                                char const* const _Format,
                                                          va_list           _ArgList
        )
    

    {
        return _vsnprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, ((void *)0), _ArgList);
    }
    

     

    

         
         
          int   vsnprintf_s(
                char*       const _Buffer,
                                                           size_t      const _BufferCount,
                                                           size_t      const _MaxCount,
                                    char const* const _Format,
                                                              va_list           _ArgList
            )
    

        {
            return _vsnprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, ((void *)0), _ArgList);
        }
    

         

    

     
      int   _vscprintf_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
                                                va_list           _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsprintf(
            (*__local_stdio_printf_options()) | (1ULL << 1),
            ((void *)0), 0, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
      int   _vscprintf(
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vscprintf_l(_Format, ((void *)0), _ArgList);
    }
    

     
      int   _vscprintf_p_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
                                                va_list           _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsprintf_p(
            (*__local_stdio_printf_options()) | (1ULL << 1),
            ((void *)0), 0, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
      int   _vscprintf_p(
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vscprintf_p_l(_Format, ((void *)0), _ArgList);
    }
    

     
      int   _vsnprintf_c_l(
                   char*       const _Buffer,
                                             size_t      const _BufferCount,
            char const* const _Format,
                                         _locale_t   const _Locale,
                                                va_list           _ArgList
        )
    

    {
        int const _Result = __stdio_common_vsprintf(
            (*__local_stdio_printf_options()),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        return _Result < 0 ? -1 : _Result;
    }
    

     
     
      int   _vsnprintf_c(
          char*       const _Buffer,
                                    size_t      const _BufferCount,
             char const* const _Format,
                                       va_list           _ArgList
        )
    

    {
        return _vsnprintf_c_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
    }
    

     
       
      int   _sprintf_l(
                   char*       const _Buffer,
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        
        
        _Result = _vsprintf_l(_Buffer, _Format, _Locale, _ArgList);
        

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   sprintf(
            char*       const _Buffer,
               char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        
        
        _Result = _vsprintf_l(_Buffer, _Format, ((void *)0), _ArgList);
        

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    
    
    
    
        
  
 int      sprintf( 
      char *  _Buffer,  
     char const*   _Format
 , ...);      
  
 int      vsprintf( 
      char *  _Buffer,  
     char const*   _Format
 , va_list _Args);
    

     
     
      int   _sprintf_s_l(
            char*       const _Buffer,
                                                   size_t      const _BufferCount,
                  char const* const _Format,
                                               _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsprintf_s_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
         
          int   sprintf_s(
                char*       const _Buffer,
                                                       size_t      const _BufferCount,
                                char const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
            _Result = _vsprintf_s_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

     

     
     
      int   _sprintf_p_l(
            char*       const _Buffer,
                                                   size_t      const _BufferCount,
                  char const* const _Format,
                                               _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsprintf_p_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _sprintf_p(
            char*       const _Buffer,
                                                   size_t      const _BufferCount,
                            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsprintf_p_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
       
      int   _snprintf_l(
            char*       const _Buffer,
                                                  size_t      const _BufferCount,
                 char const* const _Format,
                                              _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        
        
        _Result = _vsnprintf_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    



     
     
      int   snprintf(
            char*       const _Buffer,
                                                       size_t      const _BufferCount,
                                char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
    
        _Result = vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _snprintf(
            char*       const _Buffer,
                                                  size_t      const _BufferCount,
                           char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
    
        _Result = _vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

       
  
 int    _snprintf(
      char * _Buffer, 
   size_t  _BufferCount, 
     char const*  _Format
 , ...);     
  
 int    _vsnprintf(
      char * _Buffer, 
   size_t  _BufferCount, 
     char const*  _Format
 , va_list _Args);

     
     
      int   _snprintf_c_l(
                   char*       const _Buffer,
                                             size_t      const _BufferCount,
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsnprintf_c_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _snprintf_c(
          char*       const _Buffer,
                                    size_t      const _BufferCount,
             char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsnprintf_c_l(_Buffer, _BufferCount, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _snprintf_s_l(
            char*       const _Buffer,
                                                       size_t      const _BufferCount,
                                                       size_t      const _MaxCount,
                      char const* const _Format,
                                                   _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsnprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
      int   _snprintf_s(
            char*       const _Buffer,
                                                       size_t      const _BufferCount,
                                                       size_t      const _MaxCount,
                                char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsnprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     

     
      int   _scprintf_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vscprintf_l(_Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _scprintf(
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vscprintf_l(_Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _scprintf_p_l(
            char const* const _Format,
                                         _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vscprintf_p_l(_Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _scprintf_p(
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vscprintf_p(_Format, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
     
     
     
     
      int   __stdio_common_vsscanf(
                                            unsigned long long _Options,
                  char const*      _Buffer,
                                            size_t           _BufferCount,
            char const*      _Format,
                                        _locale_t        _Locale,
                                               va_list          _ArgList
        );

     
      int   _vsscanf_l(
                                 char const* const _Buffer,
            char const* const _Format,
                               _locale_t   const _Locale,
                                      va_list           _ArgList
        )
    

    {
        return __stdio_common_vsscanf(
            (*__local_stdio_scanf_options ()),
            _Buffer, (size_t)-1, _Format, _Locale, _ArgList);
    }
    

     
      int   vsscanf(
                                 char const* const _Buffer,
            char const* const _Format,
                                      va_list           _ArgList
        )
    

    {
        return _vsscanf_l(_Buffer, _Format, ((void *)0), _ArgList);
    }
    

     
      int   _vsscanf_s_l(
                                 char const* const _Buffer,
            char const* const _Format,
                               _locale_t   const _Locale,
                                      va_list           _ArgList
        )
    

    {
        return __stdio_common_vsscanf(
            (*__local_stdio_scanf_options ()) | (1ULL << 0),
            _Buffer, (size_t)-1, _Format, _Locale, _ArgList);
    }
    

    

        
        

         
          int   vsscanf_s(
                                     char const* const _Buffer,
                char const* const _Format,
                                          va_list           _ArgList
            )
    

        {
            return _vsscanf_s_l(_Buffer, _Format, ((void *)0), _ArgList);
        }
    

         

        

    

       
      int   _sscanf_l(
                                          char const* const _Buffer,
            char const* const _Format,
                                        _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsscanf_l(_Buffer, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

       
      int   sscanf(
                                char const* const _Buffer,
            char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsscanf_l(_Buffer, _Format, ((void *)0), _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _sscanf_s_l(
                                            char const* const _Buffer,
            char const* const _Format,
                                          _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));
        _Result = _vsscanf_s_l(_Buffer, _Format, _Locale, _ArgList);
        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

         
          int   sscanf_s(
                                      char const* const _Buffer,
                char const* const _Format,
            ...)
    

        {
            int _Result;
            va_list _ArgList;
            ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            
            
            _Result = vsscanf_s(_Buffer, _Format, _ArgList);
            

            ((void)(_ArgList = (va_list)0));
            return _Result;
        }
    

    

    
    

       
      int   _snscanf_l(
            char const* const _Buffer,
                                            size_t      const _BufferCount,
            char const* const _Format,
                                        _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = __stdio_common_vsscanf(
            (*__local_stdio_scanf_options ()),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

       
      int   _snscanf(
            char const* const _Buffer,
                                            size_t      const _BufferCount,
                      char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = __stdio_common_vsscanf(
            (*__local_stdio_scanf_options ()),
            _Buffer, _BufferCount, _Format, ((void *)0), _ArgList);

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    


     
      int   _snscanf_s_l(
              char const* const _Buffer,
                                              size_t      const _BufferCount,
            char const* const _Format,
                                          _locale_t   const _Locale,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = __stdio_common_vsscanf(
            (*__local_stdio_scanf_options ()) | (1ULL << 0),
            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

     
      int   _snscanf_s(
            char const* const _Buffer,
                                            size_t      const _BufferCount,
                    char const* const _Format,
        ...)
    

    {
        int _Result;
        va_list _ArgList;
        ((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = __stdio_common_vsscanf(
            (*__local_stdio_scanf_options ()) | (1ULL << 0),
            _Buffer, _BufferCount, _Format, ((void *)0), _ArgList);

        ((void)(_ArgList = (va_list)0));
        return _Result;
    }
    

    

    




     
     
     
     
     
    

        

        


         
          char*   tempnam(
              char const* _Directory,
              char const* _FilePrefix
            );

        


              int     fcloseall(void);
                     FILE*   fdopen(  int _FileHandle,   char const* _Format);
               int     fgetchar(void);
                     int     fileno(  FILE* _Stream);
               int     flushall(void);
               int     fputchar(  int _Ch);
                       int     getw(  FILE* _Stream);
                   int     putw(  int _Ch,   FILE* _Stream);
                      int     rmtmp(void);

    




 

typedef struct X
{
     int i;
} X;

X* X_Create() default;

int main()
{
    X *p = X_Create();
    return 1;
}
