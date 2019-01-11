#include <iostream>
#include <fstream>
#include<vector>
using namespace std;

struct point{
    double x;
    double y;
    double z;
};

void quickSort(vector<point> &v, int l, int r)
{

    if (l< r)
    {
        int i = l, j = r;
        double x = v[l].x;
        while (i < j)
        {
            while(i < j && v[j].x>= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                v[i++] = v[j];
            while(i < j && v[i].x< x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                v[j--] = v[i];
        }
        v[i].x = x;
        quickSort(v, l, i - 1); // 递归调用
        quickSort(v, i + 1, r);
    }
}

void quickSort2(vector<point> &v, int l, int r)
{

    if (l< r)
    {
        int i = l, j = r;
        double x = v[l].z;
        while (i < j)
        {
            while(i < j && v[j].z>= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                v[i++] = v[j];
            while(i < j && v[i].z< x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                v[j--] = v[i];
        }
        v[i].z = x;
        quickSort2(v, l, i - 1); // 递归调用
        quickSort2(v, i + 1, r);
    }
}

int find_min1(int st,int en,vector<vector<point> > v)
{
    double mins=5;
    int s=0;
    for(int i=st;i<en+1;i++)
   {
       vector<point> v1=v[i];
       quickSort(v1,0,v1.size()-1);
       int flag=1;
       double w1,w2,w;
       for(int j=1;j<v1.size();j++)
       {
           if((v1[j].x-v1[j-1].x)>0.01)
           {
              flag=flag+1;
           }
           if(flag==2)
           {
               w1=v1[j].x;
           }
           else if(flag==3)
           {
               w2=v1[j-1].x;
           }
       }
       w=w2-w1;
       if(w<mins)
       {
           mins=w;
           s=i;
       }
   }
   return s;
}

int find_min2(int st,int en,vector<vector<point> > v)
{
    double mins=5;
    int s=0;
    for(int i=st;i<en+1;i++)
   {
       vector<point> v1=v[i];
       quickSort(v1,0,v1.size()-1);
       int flag=1;
       double w;
       w=v1[v1.size()-1].x-v1[0].x;
       if(w<mins)
       {
           mins=w;
           s=i;
       }
   }
   return s;
}

int find_max(int st,int en,vector<vector<point> > v)
{
    double maxs=-1;
    int s=0;
    for(int i=st;i<en+1;i++)
   {
       vector<point> v1=v[i];
       quickSort2(v1,0,v1.size()-1);
       int flag=1;
       double w;
       w=v1[v1.size()-1].z-v1[0].z;
       if(w>maxs)
       {
           maxs=w;
           s=i;
       }
   }
   return s;
}


int main()
{
   vector<vector<point> > v1;
   vector<vector<point> > v2;
   vector<vector<point> > v;//v中存有完全的信息，按Y从小到大排列
   int s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12;//s1是胸围，s2颈围,s3腋下,s4会阴,s5臀围,s6手腕,s7脚踝,s8膝盖，s9肚脐
   point p1,p2,p3;//p1腋下，p2会阴,p3指尖
   for(int i=0;i<2000;i++)
   {
       vector<point> tmp1;
       vector<point> tmp2;
       v1.push_back(tmp1);
       v2.push_back(tmp2);
   }

   double x,y,z;
   int pos=0;
   ifstream in("test3.2.txt");
   if (!in) {cerr << "open file error\n"; return 1;}
   ofstream out("test3.7.txt");
   if (!out) {cerr << "create file error\n"; return 1;}
   int len1,len2,len;

   while (pos<1800564)
   {
      in>>x>>y>>z;
      point p;
      p.x=x;
      p.y=y;
      p.z=z;
      int s=y*100;
      if(y>0||y==0)
      {
          v1[s].push_back(p);
      }
      else
      {
          v2[-s].push_back(p);
      }
      pos++;
   }
   for(int i=0;i<200;i++)
   {
       if(v1[i].size()==0)
       {
           len1=i;
           break;
       }
   }
   for(int i=0;i<200;i++)
   {
       if(v2[i].size()==0)
       {
           len2=i;
           break;
       }
   }
   len=len1+len2;
   for(int i=0;i<len2;i++)
   {
       v.push_back(v2[len2-i-1]);
   }
   for(int i=0;i<len1;i++)
   {
       v.push_back(v1[i]);
   }
   /*for(int i=0;i<v.size();i++)
   {
       cout<<v[i][0].y<<endl;
   }*/
   in.close();
//v中按y坐标从小到大的顺序存了所有点信息

   /*for (int i=0;i<len;i++)
   {
       if(v[i][0].y>0&&v[i][0].y<0.01)
       {
           for (int j=0;j<v[i].size();j++)
           out <<v[i][j].ID<<' '<< v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<'\n';
           cout<<v[i].size();
           break;
       }
   }*/

   cout<<len<<endl;
   int st=len*0.53,en=len*0.63;
   s1=find_min1(st,en,v);
   st=len*6/7;
   en=len*8/9;
   s2=find_min2(st,en,v);
   st=len*0.43;
   en=len*0.6;
   s5=find_max(st,en,v);

   cout<<s1<<endl<<s2<<endl<<s5<<endl;

   bool flag=false,position=0;//position代表了选取的腋下点在左侧还是右侧，0左，1右

   for(int i=len-1;i>-1;i--)//求s3和p1
   {
       vector<point> v1=v[i];
       quickSort(v1,0,v1.size()-1);
       for(int j=1;j<v1.size();j++)
       {
           if((v1[j].x-v1[j-1].x)>0.01)
           {
               flag=true;
               s3=i;
               if(v1[j-1].x<0)
               {
                   position=0;
                   p1=v1[j-1];
               }
               else if(v1[j-1].x>0)
               {
                   position=1;
                   p1=v1[j];
               }
               break;

           }
       }
       if(flag)
       {
           break;
       }
   }
   cout<<s3<<endl;
   cout<<p1.x<<endl<<p1.y<<endl<<p1.z<<endl;


   for(int i=30;i<len;i++)//求s4和p2
   {
       bool flag1=true;
       vector<point> v1=v[i];
       quickSort(v1,0,v1.size()-1);
       for(int j=1;j<v1.size();j++)
       {
           if((v1[j].x-v1[j-1].x)>0.01)
           {
               flag1=false;
               p2=v1[j-1];
               break;
           }
       }
       if(flag1)
       {
           s4=i;
           break;
       }
   }
   cout<<s4<<endl;
   cout<<p2.x<<endl<<p2.y<<endl<<p2.z<<endl;

   for(int i=len-1;i>-1;i--)//求p3
   {
       if(v[i][0].y>p1.y-0.03)
       {
           continue;
       }
       else if(v[i][0].y<p2.y+0.02)
       {
           break;
       }
       if(position==1)
       {
           vector<point> v1=v[i];
           quickSort(v1,0,v1.size()-1);
           int len_tmp=v1.size(),part=1;
           for(int j=len_tmp-1;j>0;j--)
           {
               if(v1[j].x-v1[j-1].x>0.01)
               {
                   part++;
               }
           }
           if(part<3)
           {
               vector<point> v2=v[i-1];
               quickSort(v2,0,v2.size()-1);
               p3=v2[v2.size()-1];
               break;
           }

       }
       else if(position==0)
       {
           vector<point> v1=v[i];
           quickSort(v1,0,v1.size()-1);
           int len_tmp=v1.size(),part=1;
           for(int j=len_tmp-1;j>0;j--)
           {
               if(v1[j].x-v1[j-1].x>0.01)
               {
                   part++;
               }
           }
           if(part<3)
           {
               vector<point> v2=v[i-1];
               quickSort(v2,0,v2.size()-1);
               p3=v2[0];
               break;
           }
       }

   }
   cout<<p3.x<<endl<<p3.y<<endl<<p3.z<<endl;


   if(position==1)//求s6
   {
     double mins=1;
     for(int i=len-1;i>-1;i--)
     {

       if(v[i][0].y>p1.y-0.03)
       {
           continue;
       }
       else if(v[i][0].y<p3.y+0.05)
       {
           break;
       }
       else
       {

               vector<point> v1=v[i];
               vector<point> v2;
               quickSort(v1,0,v1.size()-1);
               int len_tmp=v1.size();
               for(int j=len_tmp-1;j>0;j--)
               {
                   if(v1[j].x-v1[j-1].x>0.01)
                   {
                       v2.push_back(v1[j]);
                       break;
                   }
                   else
                   {
                       v2.push_back(v1[j]);
                   }
               }
               quickSort2(v2,0,v2.size()-1);
               /* double l;
               l=v2[v2.size()-1].x-v2[0].x;
               if(l<mins)
               {
                   mins=l;
                   s6=i;
               }
               cout<<l<<endl;*/
               vector<point> v3;
               double tmp=0;
               for(int j=0;j<v2.size();j++)
               {
                   tmp+=v2[j].z;
               }
               tmp=tmp/v2.size();
               int j;
               for(j=0;j<v2.size();j++)
               {
                   if(tmp-v2[j].z<0.01)
                   {
                       v3.push_back(v2[j]);
                       break;
                   }
               }
               for(int m=j;m>0;m--)
               {
                   if((v2[m].z-v2[m-1].z)>0.01)
                   {
                       break;
                   }
                   else
                   {
                       v3.push_back(v2[m-1]);
                   }
               }
               for(int m=j;m>0;m++)
               {
                   if((v2[m+1].z-v2[m].z)>0.01)
                   {
                       break;
                   }
                   else
                   {
                       v3.push_back(v2[m+1]);
                   }
               }
               quickSort2(v3,0,v3.size()-1);

              /* vector<int>::iterator it;
               for(it=v2.begin();it!=v2.end();)
               {
                   vector<int>::iterator it2;
                   it2=it+1;
                   if()
                   {
                       it=v2.erase(it);    //删除元素，返回值指向已删除元素的下一个位置
                   }
                   else
                       ++it;    //指向下一个位置
                }
*/

               double l;
               l=v3[v3.size()-1].z-v3[0].z;
               if(l<mins)
               {
                   mins=l;
                   s6=i;
               }

       }
     }
   }
   cout<<s6<<endl;

   double mins=5;
   for(int i=20;i<len;i++)//求s7
   {
       if(v[i][0].y>p2.y-0.01)
       {
           break;
       }
       vector<point> v1=v[i];
       vector<point> v2;
       quickSort(v1,0,v1.size()-1);
       for(int j=0;j<v1.size();j++)
       {
           if((v1[j+1].x-v1[j].x)>0.01)
           {
               v2.push_back(v1[j]);
               break;
           }
           else
           {
               v2.push_back(v1[j]);
           }
       }
       double w;
       w=v2[v2.size()-1].x-v2[0].x;
       if(w<mins)
       {
           mins=w;
           s7=i;
       }
   }
   cout<<s7<<endl;
   s8=0.5*s4+0.5*s7;
   s9=s8+0.33*(s4-s8);
   s10=s8+0.67*(s4-s8);
   s11=s5+0.3*(s3-s5);
   s12=s5+0.7*(s3-s5);

   //开始写入信息
   for (int i=0;i<len;i++)
   {
       if(i==s1)
       {
           vector<point> v1=v[i];
           quickSort(v1,0,v1.size()-1);
           int flag=1;
           out << v1[0].x << ' '<<v1[0].y<<' '<<v1[0].z<<' '<<255<<' '<<0<<' '<<0<<' '<<'\n';
           for(int j=1;j<v1.size();j++)
           {
               if((v1[j].x-v1[j-1].x)>0.01)
               {
                   flag=flag+1;
               }
               if(flag==2)
               {
                   out << v1[j].x << ' '<<v1[j].y<<' '<<v1[j].z<<' '<<0<<' '<<255<<' '<<0<<' '<<'\n';
               }
               else{out<< v1[j].x << ' '<<v1[j].y<<' '<<v1[j].z<<' '<<255<<' '<<0<<' '<<0<<' '<<'\n';}
           }
       }
       else if(i==s2)
       {
           for (int j=0;j<v[i].size();j++)
           {
               out << v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<' '<<0<<' '<<0<<' '<<255<<' '<<'\n';
           }
       }
       else if(i==s3)
       {
           for (int j=0;j<v[i].size();j++)
           {
               out << v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<' '<<0<<' '<<255<<' '<<255<<' '<<'\n';
           }
       }
        else if(i==s4)
       {
           for(int j=0;j<v[i].size();j++)
           {
               out << v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<' '<<255<<' '<<0<<' '<<255<<' '<<'\n';
           }

       }
        else if(i==s5||i==s12||i==s11)
       {
            vector<point> v1=v[i];
           quickSort(v1,0,v1.size()-1);
           int flag=1;
           out << v1[0].x << ' '<<v1[0].y<<' '<<v1[0].z<<' '<<255<<' '<<0<<' '<<0<<' '<<'\n';
           for(int j=1;j<v1.size();j++)
           {
               if((v1[j].x-v1[j-1].x)>0.01)
               {
                   flag=flag+1;
               }
               if(flag==2)
               {
                   out << v1[j].x << ' '<<v1[j].y<<' '<<v1[j].z<<' '<<0<<' '<<50<<' '<<50<<' '<<'\n';
               }
               else{out<< v1[j].x << ' '<<v1[j].y<<' '<<v1[j].z<<' '<<255<<' '<<0<<' '<<0<<' '<<'\n';}
           }

       }
       else if(i==s6)
       {
           vector<point> v1=v[i];
           quickSort(v1,0,v1.size()-1);
           int flag=1;
           out << v1[0].x << ' '<<v1[0].y<<' '<<v1[0].z<<' '<<100<<' '<<100<<' '<<25<<' '<<'\n';
           for(int j=1;j<v1.size();j++)
           {
               if((v1[j].x-v1[j-1].x)>0.01)
               {
                   flag=flag+1;
               }
               if(flag==2)
               {
                   out << v1[j].x << ' '<<v1[j].y<<' '<<v1[j].z<<' '<<255<<' '<<0<<' '<<0<<' '<<'\n';
               }
               else{out<< v1[j].x << ' '<<v1[j].y<<' '<<v1[j].z<<' '<<100<<' '<<100<<' '<<25<<' '<<'\n';}
           }
       }
       else if(i==s7)
       {
           for(int j=0;j<v[i].size();j++)
            {
                 out << v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<' '<<0<<' '<<200<<' '<<100<<' '<<'\n';
            }
       }
       else if(i==s8)
       {
           for(int j=0;j<v[i].size();j++)
            {
                 out << v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<' '<<50<<' '<<100<<' '<<50<<' '<<'\n';
            }
       }
        else if(i==s9)
       {
           for (int j=0;j<v[i].size();j++)
           {
               out << v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<' '<<0<<' '<<255<<' '<<255<<' '<<'\n';
           }
       }
        else if(i==s10)
       {
           for (int j=0;j<v[i].size();j++)
           {
               out << v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<' '<<0<<' '<<0<<' '<<200<<' '<<'\n';
           }
       }
       else
        {
            for(int j=0;j<v[i].size();j++)
            {
                 out << v[i][j].x << ' '<<v[i][j].y<<' '<<v[i][j].z<<' '<<255<<' '<<0<<' '<<0<<' '<<'\n';
            }
        }


   }



   out.close();


   return 0;
}
