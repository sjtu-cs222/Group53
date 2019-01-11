#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;

const int maxn = 11000;
struct Point{
	int x;
	int y;
}points[maxn], sstack[maxn];


double mulity(Point p1, Point p2, Point p0){//注意，这里直接返回计算结果就行，不要再判断什么情况下返回1什么情况下返回0，因为这是重用度比较高的函数，是位于“底层”的，直接返回结果到上层中判断远比自己加一个判断要好得多！
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);//向量p0p1 到 向量p0p2，叉乘大于0，意味着，右手定则右手四指指向p0p1的方向握向p0p2的方向时，大拇指朝外
}

double dis(Point a, Point b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool cmp(Point p1, Point p2){//p0p1 到 p0p2
	//向量方向相同，距离短的在前（假设是B点），长的（假设是C点）在后，这样在Graham里的while循环判断中，如果恰好出现这样的极端情况：最左下角的点（假设是A）位于栈里的top-1的位置,B点位于top，C点位于i，则top--，将点A出栈，将点B进栈，然后计算距离时，这一段是计算点A到点C，正解。如果是距离远的在前，那么应当是点B位于i，点C位于top，那么while判断里因为极角相同则top--，点C出栈，点B进栈，计算这一段距离时，则是A到B，错的。围成的凸包也不对。
	double k = mulity(p1, p2, points[0]);
	if (k>0){
		return 1;
    }
    else if (k == 0 && dis(p1, points[0]) <= dis(p2, points[0])){
		return 1;
	}
	return 0;
}

int Graham(int num){
    //输入点的个数
	int top = -1;
	for (int i = 0; i<num; i++){
        //遇到i，比较i和当前栈顶元素top,谁在外围谁留下，即mulity(p1,p2,p0)，右手由p0p1 握向 p0p2，拇指朝里，则叉乘<=0，所以p2靠外所以压栈，而p1在内所以出栈。
		while ((1<top) && (mulity(points[i], sstack[top], sstack[top - 1])>0)){//mulity()>=0也是可以的
		    //while的判断语句，调试了一上午！一个是因为sstack之前用points代替，不和栈里的数做比较明显是错的，但这个地方确实很容易写错，高危！！！；另一个是因为多打了一个分号，则按while判断句按陈述语句先执行，然后因为检测到while里的判断句被执行了，所以while()内的语句一定先执行一次然后才进入下一次while里的条件语句进行判断要不要再进while循环！！
			top--;//若将i与top-1两点相连，则当前top点在内侧。所以当前top点出栈。退回到上一个top点与top-1，继续比较，直到当i入栈时，已入栈的点不会被包裹在内侧。
		}
		//i点可入栈，并且不会破坏当前栈中所有点可构成凸包（即不会出现，连接栈中任意两点使得栈中任意一点会在连线内侧的情况）
		sstack[++top] = points[i];
	}
	return top;
}

double Perimeter(int *l1,int *l2,int num)//输入范围内的二维点集坐标和点的个数
{
		//输入数据，并且找到左下角的点
		//scanf("%d%d", &points[0].x, &points[0].y);
		points[0].x=l1[0];
		points[0].y=l2[0];
		int ld_id = 0;//left down id
		for (int i = 1; i<num; i++){
			points[i].x=l1[i];
		    points[i].y=l2[i];
			if (points[ld_id].y>points[i].y){
				ld_id = i;
			}
			else if (points[ld_id].y == points[i].y&&points[ld_id].x>points[i].x){
                ld_id = i;
			}
		}
		if (num == 1){
			return 0;
		}
		else if (num == 2){
			return dis(points[0], points[1]);
		}
		//把左下角的点放到数组第一个
		Point temp = points[0];
		points[0] = points[ld_id];
		points[ld_id] = temp;
		//其他点按照与p0的极角由小到大排序，极角相同按距离由近到远排序，这样在Graham里的循环判断找凸包时，会将先进栈的最近的点踢出去，将距离最远的点留下，这样做所求的这一段距离才是对的，如果最后留下最近的点则形成的凸包漏掉了这个最远的点，所求距离自然也是过短的
		sort(points + 1, points + (num), cmp);
		//for(int i=0;i<n;i++)
            //cout<<points[i].x<<" "<<points[i].y<<endl;
		int top=Graham(num);
		double res = 0;//凸包周长
		//机智的0到top的相加..
		for (int i = 0; i <= top; i++){
			res += dis(sstack[i], sstack[(i + 1) % (top + 1)]);
		}
		return res;

}

int main()

{
    //输入两个数组，分别存储点的x,y坐标，和点的个数，输出周长
   int a[10]={12,24,30,41,80,50,22,45,50},b[10]={7,9,5,9,7,87,9,1,7},c[5]={0,0,4,1,4},d[5]={0,4,0,1,4};
   printf("%.2f\n", Perimeter(a,b,9));
   printf("%.2f\n", Perimeter(c,d,5));
//4 0 0 0 4 4 0 4 4

//9 12 7 24 9 30 5 41 9 80 7 50 87 22 9 45 1 50 7 0
}
