int num = 1;

main(){

if (*(char *)&num == 1)
{
    printf("Little-Endian\n");
}
else
{
    printf("Big-Endian\n");
}
}
