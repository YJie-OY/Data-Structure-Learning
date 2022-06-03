
#ifndef MYVECTOR
#define MYVECTOR

#include<algorithm>
#include<utility>
#include<assert.h>

template <typename T>
class Vector
{
	public:
		typedef int pos_t;
		static const int SPARE_CAPACITY  = 10;
	private:

		T* v;
		size_t siz;
		size_t cap;

	public: // ���⺯����ʵ��

		explicit Vector(size_t initSize = 0,size_t initCapacity = 0,int x=0);
		~Vector();
	
	public: // ���ʺ�����ʵ��

		// ��ѯ���ݼ���ģ
		size_t size() const;

		// ��ѯ����
		size_t capacity() const;

		// �ж����ݼ��Ƿ�Ϊ��
		bool empty() const;

		// ������������
		void reserve(size_t newCapacity)
		{
			T* tmp = new T[newCapacity];
			// ������С�����ݼ���ʱ��,���Ǽ���һ�������ݼ�
			if(newCapacity <= siz)
			{
				for(int i=0 ; i<newCapacity ; ++i)
					tmp[i]=v[i];
				siz = newCapacity;
			}
			else
			{
				// �����������ʱ�򣬰�ԭ�������ݸ��ƹ���
				for(int i=0 ; i<siz ; ++i)
					tmp[i]=v[i];					
			}

			delete[] v;
			v = tmp;
			cap = newCapacity;
		}

		// �������ݼ���ģ
		void resize (size_t newSize,const T& x=T())
		{
			if(newSize <= cap)
			{
				if(siz < newSize)
					for(int i=siz ; i<newSize ; ++i )
						v[i] = x;
				siz = newSize ;
				return ;
			}
			else
			{
				T* tmp=new T[newSize + SPARE_CAPACITY]; // ��������һ�������ڴ�ռ�

				for(int i=0;i<siz;++i) 					// �Ƚ�ԭ�����е����ݸ��ƹ���
					tmp[i]=v[i];

				for(int i=siz;i<newSize;++i)				// ����������ݳ�ʼ��Ϊָ����ֵ
					tmp[i]=x;

				delete[] v;								// �ͷ�ԭ�����ڴ�ռ�
				v = tmp;									// ָ���µ��ڴ�ռ� 
				siz = newSize;							// ά�����ݼ���ģ
				cap = newSize + SPARE_CAPACITY;			// ά���µ�����
				return ;
			}				 
		}


		// ��ĩβ������ֵԪ��
		void push_back(const T& x)
		{
			if(siz + 1 <= cap)
				v[siz++]=x;
			else
			{
				T* tmp=new T[siz+1 + SPARE_CAPACITY]; // ��������һ�������ڴ�ռ�

				for(int i=0;i<siz;++i) 					// �Ƚ�ԭ�����е����ݸ��ƹ���
					tmp[i]=v[i];

				tmp[siz] = x;

				delete[] v;								// �ͷ�ԭ�����ڴ�ռ�
				v = tmp;									// ָ���µ��ڴ�ռ� 
				siz++;						// ά�����ݼ���ģ
				cap = siz + SPARE_CAPACITY;			// ά���µ�����
			}
		}

		// ��ĩβ������ֵԪ��
		void push_back(T&& x) //��ֵ���� 
		{
			if(siz + 1 <= cap)
				v[siz++]=std::move(x);
			else
			{
				T* tmp=new T[siz+1 + SPARE_CAPACITY]; // ��������һ�������ڴ�ռ�

				for(int i=0;i<siz;++i) 					// �Ƚ�ԭ�����е����ݸ��ƹ���
					tmp[i]=v[i];

				tmp[siz] = std::move(x);

				delete[] v;								// �ͷ�ԭ�����ڴ�ռ�
				v = tmp;									// ָ���µ��ڴ�ռ� 
				siz++;						// ά�����ݼ���ģ
				cap = siz + SPARE_CAPACITY;			// ά���µ�����
			}
			
		}

		// ɾ��ĩβԪ��
		void pop_back()
		{
			if(siz == 0) return;
			else
				--siz;
		}

		// ���ײ�����һ����ֵԪ��
		void push_front(const T& x)
		{
			T* tmp = new T[siz+1 + SPARE_CAPACITY];
			tmp[0] = x;
			for(int i=1 ; i<siz+1 ; i++)
				tmp[i] = v[i-1];
			delete[] v;
			v = tmp;
			siz++;
			cap = siz + SPARE_CAPACITY;
		}

		// ���ײ�����һ����ֵԪ��
		void push_front(T&& x)
		{
			T* tmp = new T[siz+1 + SPARE_CAPACITY];
			tmp[0] = std::move(x);
			for(int i=1 ; i<siz+1 ; i++)
				tmp[i] = v[i];
			delete[] v;
			v = tmp;
			siz++;
			cap = siz + SPARE_CAPACITY;			
		}

		// ɾ���ײ���Ԫ��
		void pop_front()
		{
			T* tmp = new T[siz + SPARE_CAPACITY];
			for(int i=0 ; i<siz-1 ; i++)
				tmp[i] = v[i+1];
			delete[] v;
			v = tmp;
			siz--;
			cap = siz + SPARE_CAPACITY;
		}

		// ��λ�� pos ����Ԫ��
		pair<bool,pos_t> insert(pos_t pos,const T& x)
		{
			if(siz+1 > cap or pos > siz)
				return pair<bool,pos_t>(false,pos);
			else
			{
				T* tmp = new T[siz+1 + SPARE_CAPACITY];
				for(int i=0 ; i<pos ; i++)
					tmp[i] = v[i];
				tmp[pos] = x;
				for(int i=pos+1 ; i<siz+1 ; ++i)
					tmp[i] = v[i-1];

				delete[] v;
				v = tmp;
				siz++;
				cap = siz + SPARE_CAPACITY;
				return pair<bool,pos_t>(true,pos);
			}
		}

		// ɾ����λ�� Pos �ϵ�Ԫ��
		pair<bool,pos_t> erase(pos_t pos)
		{
			if(pos > siz)
				return pair<bool,pos_t>(false,pos);
			else
			{
				T* tmp = new T[siz + SPARE_CAPACITY];
				for(int i=0 ; i<pos ; i++)
					tmp[i] = v[i];
				for(int i=pos ; i<siz-1 ; i++)
					tmp[i] = v[i+1];
				
				delete[] v;
				v = tmp;
				siz--;
				cap = siz + SPARE_CAPACITY;
				return pair<bool,pos_t>(true,pos);
			}
			
		}

		// ���������������λ�� pos ��Ԫ�أ���֧���޸�
		const T& operator[](pos_t pos) const {return v[pos];}

		// ���������������λ�� pos ��Ԫ�أ�֧���޸�
		T& operator[](pos_t pos){return v[pos];}

		// ����λ�� pos ��Ԫ�أ���֧���޸�	
		const T& at(pos_t pos) const
		{
			assert(pos>=0 && pos<siz);
			return v[pos];
		}

		// ����λ�� pos ��Ԫ�أ�֧���޸�
		T& at(pos_t pos)
		{
			assert(pos>=0 && pos<siz);
			return v[pos];
		}
};


#endif
/* ========= ���ݳ�Ա���� ==========
	template <typename T>
	typedef T value_type
	typedef size_t size_type
	

/*


/* ���нӿ�-���ⷽ����
	explict vector(size_t,size_t)		// ��ʾ���캯�����ܾ�ǿ��ת����

*/

/*
���нӿ�-һ�㷽����
	size_t size() const; 		// ��ѯ���ݼ���ģ
	size_t capcity() const;		// ��ѯ����
	
	bool empty() const; 		// �ж����ݼ��Ƿ�Ϊ��

	const T& operator[](pos_t pos) const // ��ѯλ�� pos �ϵ�Ԫ�أ��������޸�,�������߽���
	T& operator[](pos_t pos)			 // ��ѯλ�� pos �ϵ�Ԫ�أ������޸ģ��������߽���

	const T& at(pos_t pos) const		// ��ѯλ�� Pos �ϵ�Ԫ�أ��������޸ģ������߽���
	T& at(pos_t pos) 					// ��ѯλ�� pos �ϵ�Ԫ�أ������޸ģ������߽���

	void push_back()		// ĩβ����Ԫ��
	void push_front()		// �ײ�����Ԫ��
	void pop_back()			// ĩβɾ��Ԫ��
	void pop_front()		// �ײ�ɾ��Ԫ��
	pair<bool,pos_t> insert(pos_t,int)	// ��λ�� pos ����Ԫ��
	pair<bool,pos_t> erase(pos_t)		// ɾ��λ�� pos �ϵ�Ԫ��

	void clear() 			// ɾ�����������е�Ԫ��

	void resize()			// �޸����ݼ���ģ
	void reserve()			// �޸�����������


*/
