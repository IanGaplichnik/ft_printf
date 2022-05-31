if (flag #)
{
	if (conv 'o')
		0 prepend
	if (conv 'x' 'X')
		0x prepend
}
if (flag '0')
{
	prepend many 0
}
if (flag '-')
{
	align left
}
if (flag '+')
{
	if (value[0] != '-')
		prepend +
}
if (flag ' ')
{
	if (value[0] != '-')
		prepend ' '
}


if (parse->width && parse->width > num_len)
{
	if (!flag '0')
		prepend ' '
	else
		prepend '0'
}

0x in the end

precision shows MINIMUM NUMBER
width shows MINIMUM width

if width < precision
	ignore width
	
if width > output number && flag space
	don't add space

minus plus 0x added at the very end and not considered as number/digit 




if number is shorter than precision, add zeroes (regardless of signs)
if x && #, prepend 0x
if +, prepend +
if ' ' && !- && !+, prepend ' '
if '0' && number not negative, prepend 0