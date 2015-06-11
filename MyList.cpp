#include<iostream>
using namespace std;

void qs1(int l,int r, int a[])		//quicksort from small to big.
{
     int i,j,mid,t;
     i=l;j=r;mid=a[(i+j)/2];
     while(i<=j)
     {
           while(a[j]>mid) j--;
           while(a[i]<mid) i++;
           if(i<=j)
           {
                   t=a[i];a[i]=a[j];a[j]=t;
                   i++;j--;
           }     
     }
     if(l<j) qs1(l,j,a);
     if(i<r) qs1(i,r,a);
}

void qs2(int l,int r, int a[])		//quicksort from big to small.
{
     int i,j,mid,t;
     i=l;j=r;mid=a[(i+j)/2];
     while(i<=j)
     {
           while(a[j]<mid) j--;
           while(a[i]>mid) i++;
           if(i<=j)
           {
                   t=a[i];a[i]=a[j];a[j]=t;
                   i++;j--;
           }     
     }
     if(l<j) qs2(l,j,a);
     if(i<r) qs2(i,r,a);
}

template<class T>
class MyList{
private:
	T *a;
	int size;
	int num;				//to remind the number of the list.
	void double_space(){
		T *b;
		b = new T [size];
		for(int i=0; i<num; ++i) b[i]=a[i];
		delete [] a;
		a = new T [size*2];
		size *= 2;
		for(int i=0; i<num; ++i) a[i]=b[i];
		delete [] b;
	}
	
public:
	MyList(){
		size = 100;
		num = 0;
		a = new T [size];
	}
	
	MyList(int cnum, const T &item){
		size = cnum;
		num = 0;
		a = new T [size];
		for(int i=0; i<cnum; ++i){
			a[i]=item;
			++num;
		}
	}
	
	MyList(const MyList &l){
		size = l.size;
		num = 0;
		a = new T [size];
		for(int i=0; i<size; ++i){
			a[i] = l.a[i];
			++num;
		}
	}
	
    MyList(T* arr, int len){
    	size = len;
    	num = 0;
    	a = new T [size];
    	for(int i=0; i<len; ++i){
    		a[i] = arr[i];
    		++num;
		}
	}

	void push(const T &item){		//push at last one.
		if(num==size) double_space();
		a[num] = item;
		++num;
	}
	
	T pop(){				//if a is empty, then can't pop. program will exit.
		try{
			if(num==0) throw 1;
			else{
				--num;
				return a[num];
			}
		}
		catch(int i){
			exit(-1);
		}
	}
	
	void insert(int index, const T &item){			
		if(index>=num) index=num;		//if index>=num, then insert at last, same to push.
		T *b;
		b = new T [size];
		for(int i=index; i<num; ++i) b[i]=a[i];
		if(num>size-1) double_space();
		a[index] = item;
		for(int i=index; i<num; ++i) a[i+1]=b[i];
		++num;
		delete [] b;
	}
	
	void clean(){		//clean the list.
		num = 0;
	}
	
	int get_size(){
		return num;
	}
	
	void erase(int start, int end){
		if(start<0) start=start+num;		//if start or end <0, then like Python to deal with. 
		if(end<0) end=end+num;		
		if(start<num && start<end){		//if start>=num or start>end, do nothing. because there is nothing to erase. 
			for(int i=0; i<num-end-1; ++i) a[i+start]=a[i+end+1];
			num -= end-start+1;
		}
	}
	
	T get_item(int index){
		try{
			if(index<0) index=num+index;		//if index<0, like Python to deal with.
			if(index>=num) throw 1;			//if index>=num, runtime error.
			else return a[index];
		}
		catch(int i){
			exit(-1);
		}
	}
	
	MyList get_item(int start, int end){
		if(start<0) start=num+start;		//if start or end <0, like Python.
		if(end<0) end=num+end;
		MyList<T> tmp;
		if(start<num) for(int i=0; i<end-start+1; ++i) tmp.push(a[i+start]);	//if start<num or start<end, return empty list.
		return tmp;
	}
	
	int count(const T &item){		//count the number of item.
		int cnt=0;
		for(int i=0; i<num; ++i) if(a[i]==item) ++cnt;
		return cnt;
	}
	
	void remove(const T &item){		//remove the first item in list.
		for(int i=0; i<num; ++i){
			if(a[i]==item){
				erase(i, i);
				break;
			}
		}
	}

	MyList operator + (const MyList &l){		//add two list.
		MyList<T> tmp;
		while(tmp.size<num+l.num) tmp.double_space();
		for(int i=0; i<num; ++i){
			tmp.a[i]=a[i];
			++tmp.num;
		}
		for(int i=0; i<l.num; ++i){
			tmp.a[i+num]=l.a[i];
			++tmp.num;
		}
		return tmp;
	}
    
	MyList operator + (const T &item){		//add a item. return a new list.
		MyList<T> tmp;
		if(tmp.size<num+1) tmp.double_space();
		for(int i=0; i<num; ++i){
			tmp.a[i]=a[i];
			++tmp.num;
		}
		tmp.a[num] = item;
		++tmp.num;
		return tmp;
	}
	
	MyList &operator = (const MyList &l){		//give the value.
		if(this == &l) return *this;
		delete [] a;
		size = l.size;
		num = l.num;
		a = new T [size];
		for(int i=0; i<num; ++i) a[i] = l.a[i];
		return *this;
	}
	
	MyList &operator += (const T &item){		//same to push.
		if(num==size) double_space();
		a[num]=item;
		++num;
		return *this;
	}
	
	MyList &operator += (const MyList &l){		//add a list to this.
		while(size<num+l.num) double_space();
		for(int i=0; i<l.num; ++i){
			a[num] = l.a[i];
			++num;
		}
		return *this;
	}
	
	T &operator [](int index){
		if(index<0) index = index + num;
		try{		
			if(index>=num) throw 1;		//runtime error.
			else return a[index];
		}
		catch(int i){
			exit(-1);
		}
	}
	
	friend ostream & operator<<(ostream &os, const MyList<T> &obj){
		os<<"[";
		for(int i=0; i<obj.num-1; ++i) os<<obj.a[i]<<", ";
		if(obj.num>0) os<<obj.a[obj.num-1];			//if the list is empty, then cout [].
		os<<"]";
		return os;
	}

	void sort(bool less=true){			//use quicksort.
		if(less) qs1(0, num-1, a);
		else qs2(0, num-1, a);
	}
	
	void reverse(){			//reverse the list.
		T *b;
		b = new T [size];
		for(int i=0; i<num; ++i) b[num-i-1] = a[i];
		for(int i=0; i<num; ++i) a[i] = b[i];
		delete [] b;
	}

	~MyList(){delete [] a;}		//delete the list.
};

int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)	// a = [0, 1, 2, 3, 4]
		a.push(i);
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = []
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 1, 0, 12]
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12]
	b.insert(3, 116); // b = [15, 4, 1, 116, 0, 12, 15, 4, 1, 0, 12]
	b.remove(4); // b = [15, 1, 116, 0, 12, 15, 4, 1, 0, 12]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}




