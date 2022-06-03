#include "Lheap.h"
#include <iostream>
#include <initializer_list>
#include "sim_iobtr_Lheap.h"
using namespace std;

typedef DSAA::Lheap<int>     queue_type;
typedef queue_type::size_type size_type;
typedef queue_type::node_type node_type;
typedef queue_type::node_ptr  node_ptr;

namespace DSAA
{
    ostream& operator<< (ostream& os, const node_type& rhs)
    {
        return os << '[' << rhs.data << ']';
    }
}

int main( )
{
    int numItems = 31;
    queue_type q1;
    
    cout<<" ==================  test for constructor(initilizer_list)=================="<<endl;
    queue_type q2 = {1,2,3,4,5,6123,123,4235,345};
    cout<<"the size of the q2 is : " << q2.size() <<endl;
    cout<<q2<<endl;


    cout<<" ==================  test for insert() =================="<<endl;
    for(int i=0 ; i<numItems ; i++)
        q1.insert(rand());
    cout<<"the q1 is like : "<<endl;
    cout<<q1<<endl;

    cout<<" ==================  test for findmin =================="<<endl;
    cout<<"the minimum of the q1 is : " << q1.findMin()<<endl;
    cout<<"the minimum of the q2 is : " << q2.findMin()<<endl;

    cout<<" ==================  test for deletemin =================="<<endl;
    q1.deleteMin();
    cout<<"After deleteMin() , the q1 is like : "<<endl;
    cout<<q1<<endl;


    cout<<" ==================  test for operator = (rhs) =================="<<endl;
    queue_type q3 = q2;
    cout<<"the q3 is like (constructed by q2) : "<<endl;
    cout<<q3<<endl;


    cout<<" ==================  test for isEmpty() and makeEmpty() =================="<<endl;
    cout<<"the q3 is "<<(q3.isEmpty()?"empty ":"not empty ") << "without makeEmpty()"<<endl;
    q3.makeEmpty();
    cout<<"the q3 is "<<(q3.isEmpty()?"empty ":"not empty ") << "after   makeEmpty()"<<endl;
    

    cout<<" ==================  test for merge() =================="<<endl;
    q1.merge(q2);
    cout<<"After merge the q2 , the q1 is like : "<<endl << q1 <<endl;

    cout<<" ==================  test for swap() =================="<<endl;
    for(int i=0 ; i<23 ; i++)
        q3.insert(rand());
    q1.swap(q3);
    cout<<"the q3 is like : " <<endl << q3 << endl;
    cout<<"After swap with the q3 , the q1 is like : " << endl << q1 << endl;
    cout<<"After swap with the q1 , the q3 is like : " << endl << q3 << endl;

    cout<<" ==================  test for size() =================="<<endl;
    cout<<"the size of the q1 is : " << q1.size() << endl;



    

    

    return 0;
}
