template <typename tipeku>
tipeku urutkan(tipeku *p, int n)
{
	tipeku x;

   for(int j=1; j<n; j++)
   {
   	for(int k=(n-1); k>=1; k--)
      {
      	if(p[k-1]>p[k])
         {
         	x=p[k-1];
            p[k-1]=p[k];
            p[k]=x;
         }
      }
   }
   return 0;
}
