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


double mulity(Point p1, Point p2, Point p0){//ע�⣬����ֱ�ӷ��ؼ��������У���Ҫ���ж�ʲô����·���1ʲô����·���0����Ϊ�������öȱȽϸߵĺ�������λ�ڡ��ײ㡱�ģ�ֱ�ӷ��ؽ�����ϲ����ж�Զ���Լ���һ���ж�Ҫ�õö࣡
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);//����p0p1 �� ����p0p2����˴���0����ζ�ţ����ֶ���������ָָ��p0p1�ķ�������p0p2�ķ���ʱ����Ĵָ����
}

double dis(Point a, Point b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool cmp(Point p1, Point p2){//p0p1 �� p0p2
	//����������ͬ������̵���ǰ��������B�㣩�����ģ�������C�㣩�ں�������Graham���whileѭ���ж��У����ǡ�ó��������ļ�������������½ǵĵ㣨������A��λ��ջ���top-1��λ��,B��λ��top��C��λ��i����top--������A��ջ������B��ջ��Ȼ��������ʱ����һ���Ǽ����A����C�����⡣����Ǿ���Զ����ǰ����ôӦ���ǵ�Bλ��i����Cλ��top����ôwhile�ж�����Ϊ������ͬ��top--����C��ջ����B��ջ��������һ�ξ���ʱ������A��B����ġ�Χ�ɵ�͹��Ҳ���ԡ�
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
    //�����ĸ���
	int top = -1;
	for (int i = 0; i<num; i++){
        //����i���Ƚ�i�͵�ǰջ��Ԫ��top,˭����Χ˭���£���mulity(p1,p2,p0)��������p0p1 ���� p0p2��Ĵָ�������<=0������p2��������ѹջ����p1�������Գ�ջ��
		while ((1<top) && (mulity(points[i], sstack[top], sstack[top - 1])>0)){//mulity()>=0Ҳ�ǿ��Ե�
		    //while���ж���䣬������һ���磡һ������Ϊsstack֮ǰ��points���棬����ջ��������Ƚ������Ǵ�ģ�������ط�ȷʵ������д����Σ����������һ������Ϊ�����һ���ֺţ���while�жϾ䰴���������ִ�У�Ȼ����Ϊ��⵽while����жϾ䱻ִ���ˣ�����while()�ڵ����һ����ִ��һ��Ȼ��Ž�����һ��while��������������ж�Ҫ��Ҫ�ٽ�whileѭ������
			top--;//����i��top-1������������ǰtop�����ڲࡣ���Ե�ǰtop���ջ���˻ص���һ��top����top-1�������Ƚϣ�ֱ����i��ջʱ������ջ�ĵ㲻�ᱻ�������ڲࡣ
		}
		//i�����ջ�����Ҳ����ƻ���ǰջ�����е�ɹ���͹������������֣�����ջ����������ʹ��ջ������һ����������ڲ�������
		sstack[++top] = points[i];
	}
	return top;
}

double Perimeter(int *l1,int *l2,int num)//���뷶Χ�ڵĶ�ά�㼯����͵�ĸ���
{
		//�������ݣ������ҵ����½ǵĵ�
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
		//�����½ǵĵ�ŵ������һ��
		Point temp = points[0];
		points[0] = points[ld_id];
		points[ld_id] = temp;
		//�����㰴����p0�ļ�����С�������򣬼�����ͬ�������ɽ���Զ����������Graham���ѭ���ж���͹��ʱ���Ὣ�Ƚ�ջ������ĵ��߳�ȥ����������Զ�ĵ����£��������������һ�ξ�����ǶԵģ���������������ĵ����γɵ�͹��©���������Զ�ĵ㣬���������ȻҲ�ǹ��̵�
		sort(points + 1, points + (num), cmp);
		//for(int i=0;i<n;i++)
            //cout<<points[i].x<<" "<<points[i].y<<endl;
		int top=Graham(num);
		double res = 0;//͹���ܳ�
		//���ǵ�0��top�����..
		for (int i = 0; i <= top; i++){
			res += dis(sstack[i], sstack[(i + 1) % (top + 1)]);
		}
		return res;

}

int main()

{
    //�����������飬�ֱ�洢���x,y���꣬�͵�ĸ���������ܳ�
   int a[10]={12,24,30,41,80,50,22,45,50},b[10]={7,9,5,9,7,87,9,1,7},c[5]={0,0,4,1,4},d[5]={0,4,0,1,4};
   printf("%.2f\n", Perimeter(a,b,9));
   printf("%.2f\n", Perimeter(c,d,5));
//4 0 0 0 4 4 0 4 4

//9 12 7 24 9 30 5 41 9 80 7 50 87 22 9 45 1 50 7 0
}
