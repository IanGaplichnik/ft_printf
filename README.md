# ft_printf
```ft_printf(const char *format, ...)```  
_ft_printf_ is a project, aimed to implement _printf_ function, which is a part of a standard C library, only using functions _write, malloc_ and _free_.

As an addition, _vasprintf_ and _asprintf_ functions were built (prototypes are _ft_vasprintf_ and _ft_asprintf_ respectively).

In order to increase the speed, I have decided to build the resulting string at first, and then output the whole string with just one _write_ function call completely.
To achieve this, I am saving processed string in a linked list, as I find it to be one of the best solutions in C, to deal with dynamic allocation.

For instance:  
```ft_printf("Hello %-7s, this is an example", "World");```  
function call will save the part before the percent sign into the first node of the linked list, resulting in a "Hello " string, 
then %7s will be processed as "World  " and saved in the second node, and the rest will be saved in the third node.
The result will look as this:  
  
_|Hello | -> |&nbsp;&nbsp;World| -> |, this is an example|_
  
  
After that, a string, which length is the same as sum of lengths of all strings of the list is allocated, content of the list is copied into the string
and outputed to the standard output with a  
```write(1, string, length_of_the_string)```

Supported features:
| flag                                                                                                                                                                                                                                                                                 | width                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   | .precision                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       | length modifier                                                                                                 | conversion specifier             |
|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|----------------------------------|
| ```#```<br><br>with _%o_:<br>first character of the output is made to be "0" by prefixing<br><br>with _%xX_:<br>non-zero result has "0x" or "0X" (respectively to conversion) prepended<br><br>with _%f_:<br>result will always contain decimal point, even if no digits follow it   | Optional decimal string (with non-zero digit first), specifying a minimum field width. If converted value has fewer characters, than the field width, it will be padded with spaces on the left (by default).<br><br>Instead of decimal digit you may write ```*```, to specify, that the field width is given in the next argument, which must be of type _int_.<br><br>A negative field width is taken as a ```-``` flag, followed by a positive field width. In no case does small field width truncate a field. Field is expanded to contain the conversion result. | Optional precision ```.``` followed by a decimal digit string.<br><br>Instead of decimal digit you may write ```*```, to specify, that the field width is given in the next argument, which must be of type _int_.<br><br>If precision is given as ```.```, precision is taken to be ```0```.<br><br>Negative precision omits precision. Precision gives the minimum number of digits to appear for _%diouxX%, the number of digits to appear after the radix character for _%f_, maximum number of characters to be printed from a string _%s_. | with _%diouxX_<br><br>```hh```<br>following integer conversion corresponds to a signed char                     | ```c```<br>char                  |
| ```0```<br>the value should be zero-padded, if width is larger, than the length of the number. Otherwise, it is ignored.<br><br>with _%diouxXf_<br>the converted value is padded on the left with zeroes, rather than blanks<br><br>if ```-``` flag is used, ```0``` flag is ignored |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  | with _%diouxX_<br><br>```h```<br>following integer conversion corresponds to a short or unsigned char           | ```s```<br>string                |
| ```-```<br>the converted value is to be adjusted on the field boundary (the default is right justification). The value is padded on the right with blanks.<br><br>if ```-``` flag is used, ```0``` flag is ignored                                                                   |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  | with _%diouxX_<br><br>```ll```<br>following integer conversion corresponds to a long long or unsigned long long | ```p```<br>pointer               |
| ```+```<br>a sign (_+_ if value is positive, _-_ if value is negative) should always be placed before a number. By default, a sign is used only for negative values (even without ```+``` flag).<br><br>if ```+``` flag is used, ```space``` flag is ignored                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  | with _%diouxXf_<br><br>```l```<br>integer conversion corresponds to a long or unsigned long argument            | ```d```<br>integer               |
| ```space```<br><br>a blank should be left before a positive number (or an empty string), produced by a signed conversion.<br><br>if ```+``` flag is used, ```space``` flag is ignored                                                                                                |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  | with  _%f_<br><br>```L```<br>conversion corresponds to long double                                              | ```i```<br>integer               |
| ```%```<br>displays a precent sign                                                                                                                                                                                                                                                   |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |                                                                                                                 | ```o```<br>unsigned octal        |
|                                                                                                                                                                                                                                                                                      |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |                                                                                                                 | ```u```<br>unsigned decimal      |
|                                                                                                                                                                                                                                                                                      |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |                                                                                                                 | ```xX```<br>unsigned hexadecimal |
|                                                                                                                                                                                                                                                                                      |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |                                                                                                                 | ```f```<br>double                |
|                                                                                                                                                                                                                                                                                      |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |                                                                                                                 | ```b```<br>prints binary
