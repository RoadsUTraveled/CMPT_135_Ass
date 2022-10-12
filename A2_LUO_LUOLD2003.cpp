//
//  main.cpp
//  A2
//
//  Created by Elijah Luo on 2021-07-21.
//  Student ID: LUOLD2003


#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;
class Quadrilateral
{
private:
    double length1, length2, width1, width2; static int count;
public:
    Quadrilateral();
    Quadrilateral(const double &len1, const double &len2, const double &wid1, const double &wid2);
    Quadrilateral(const Quadrilateral &);
    
    virtual ~Quadrilateral();
    
    virtual double getLength1() const;
    virtual double getLength2() const;
    virtual double getWidth1() const;
    virtual double getWidth2() const;
    virtual string getType() const = 0;
    static int getCount();
    
    virtual void setLength1(const double &len1);
    virtual void setLength2(const double &len2);
    virtual void setWidth1(const double &wid1);
    virtual void setWidth2(const double &wid2);
    virtual double getArea() const = 0;
    double getPerimeter() const;
    virtual void printInfo(ostream &) const = 0;
    bool operator == (const Quadrilateral &q) const;
    friend ostream& operator << (ostream &out, const Quadrilateral &q);
};
int Quadrilateral::count = 0; typedef Quadrilateral* QuadPtr;

Quadrilateral::Quadrilateral()
{
        length1 = 1;
        length2 = 2;
        width1 = 3;
        width2 = 4;
        count++;
}
Quadrilateral::Quadrilateral(const double &len1, const double &len2, const double &wid1, const double &wid2)
{
    length1 = len1;
    length2 = len2;
    width1 = wid1;
    width2 = wid2;
    count++;
}
Quadrilateral::Quadrilateral(const Quadrilateral &q)
{
    this->length1 = q.getLength1();
    this->length2 = q.getLength2();
    this->width1 = q.getWidth1();
    this->width2 = q.getWidth2();
    count++;
}
Quadrilateral::~Quadrilateral()
{
    count--;
}
double Quadrilateral::getLength1() const
{
    return length1;
}
double Quadrilateral::getLength2() const
{
    return length2;
}
double Quadrilateral::getWidth1() const
{
    return width1;
}
double Quadrilateral::getWidth2() const
{
    return width2;
}
int Quadrilateral::getCount()
{
    return count;
}
void Quadrilateral::setLength1(const double &len1)
{
    this->length1 = len1;
}
void Quadrilateral::setLength2(const double &len2)
{
    this->length2 = len2;
}
void Quadrilateral::setWidth1(const double &wid1)
{
    this->width1 = wid1;
}
void Quadrilateral::setWidth2(const double &wid2)
{
    this->width2 = wid2;
}
double Quadrilateral::getPerimeter() const
{
    return length1+length2+width1+width2;
}
bool Quadrilateral::operator == (const Quadrilateral &q) const
{
    if (this->getType() != q.getType()) return false;
    double d1 = abs(this->length1 - q.length1);
    double d2 = abs(this->length2 - q.length2);
    double d3 = abs(this->width1 - q.width1);
    double d4 = abs(this->width2 - q.width2);
    if (d1 < 1.0e-6 && d2 < 1.0e-6 && d3 < 1.0e-6 && d4 < 1.0e-6)
        return true;
    else
        return false;
}
ostream& operator << (ostream &out, const Quadrilateral &q)
{
    out.setf(ios::fixed | ios::left);
    q.printInfo(out);
    out.unsetf(ios::fixed | ios::left);
    out.precision(0);
    return out;
}

class Trapezoid : public Quadrilateral
{
public:
    Trapezoid();
    Trapezoid(const double &len1, const double &len2, const double &wid);
    Trapezoid(const Trapezoid&);
    
    double getWidth() const;
    
    virtual void setWidth1(const double &wid1);
    virtual void setWidth2(const double &wid2);
    virtual void setWidth(const double &wid);
    
    virtual string getType() const;
    virtual double getArea() const;
    virtual void printInfo(ostream&) const;
};
Trapezoid::Trapezoid() : Quadrilateral(1, 3, 2, 2)
{}
Trapezoid::Trapezoid(const double &len1, const double &len2, const double &wid) : Quadrilateral(len1, len2, wid, wid)
{
    double x = abs(getLength1() - getLength2())/2;
    while (getWidth() <= x)
        setWidth(2*getWidth());
}
Trapezoid::Trapezoid(const Trapezoid&t)
{
    this->setLength1(t.getLength1());
    this->setLength2(t.getLength2());
    this->setWidth(t.getWidth());
}
double Trapezoid::getWidth() const
{
    return this->getWidth1();
}
void Trapezoid::setWidth1(const double &wid1)
{
    setWidth(wid1);
}
void Trapezoid::setWidth2(const double &wid2)
{
    setWidth(wid2);
}
void Trapezoid::setWidth(const double &wid)
{
    this->Quadrilateral::setWidth1(wid);
    this->Quadrilateral::setWidth2(wid);
}
string Trapezoid::getType() const
{
    return "Trapezoid";
}
double Trapezoid::getArea() const
{
    double a = pow(this->getWidth1(),2.0);
    double b = pow((0.5 * abs(this->getLength1() - this->getLength2())), 2.0);
    double h = sqrt(a - b);
    return 0.5 * (this->getLength1() + this->getLength2()) * h;
}
void Trapezoid::printInfo(ostream &out) const
{
    out << setw(12) << getType() + ": ";
    out << "len1 = " << setprecision(2) << getLength1() << ", ";
    out << "len2 = " << setprecision(2) << getLength2() << ", ";
    out << "Wid = " << setprecision(2) << getWidth() << ", ";
    out << "Area = " << setprecision(2) << getArea() << ", ";
    out << "Per. = " << setprecision(2) << getPerimeter();
}

class Rectangle : public Trapezoid
{
public:
    Rectangle();
    Rectangle(const double &len, const double &wid);
    Rectangle(const Rectangle &);
    
    double getLength() const;
    
    virtual void setLength1(const double &len1);
    virtual void setLength2(const double &len2);
    virtual void setLength(const double &len);
    
    virtual  string getType() const;
    virtual double getArea() const;
    virtual void printInfo(ostream&) const;
};
Rectangle::Rectangle() : Trapezoid(1, 1, 2)
{}
Rectangle::Rectangle(const double &len, const double &wid) : Trapezoid(len, len, wid)
{}
Rectangle::Rectangle(const Rectangle &r)
{
    this->setLength(r.getLength());
    this->setWidth(r.getWidth());
}
double Rectangle::getLength() const
{
    return this->getLength1();
}
void Rectangle::setLength1(const double &len1)
{
    setLength(len1);
}
void Rectangle::setLength2(const double &len2)
{
    setLength(len2);
}
void Rectangle::setLength(const double &len)
{
    this->Quadrilateral::setLength1(len);
    this->Quadrilateral::setLength2(len);
}
string Rectangle::getType() const
{
    return "Rectangle";
}
double Rectangle::getArea() const
{
    return this->getLength() * this->getWidth();
}
void Rectangle::printInfo(ostream &out) const
{
    out << setw(12) << getType() + ": ";
    out << "len = " << setprecision(2) << getLength() << ", ";
    out << "Wid = " << setprecision(2) << getWidth() << ", ";
    out << "Area = " << setprecision(2) << getArea() << ", ";
    out << "Per. = " << setprecision(2) << getPerimeter();
}

class Square : public Rectangle
{
public:
    Square();
    Square(const double &side);
    Square(const Square &);
    
    double getSide() const;
    
    virtual void setLength1(const double &len1);
    virtual void setLength2(const double &len2);
    virtual void setLength(const double &len);
    virtual void setWidth1(const double &wid1);
    virtual void setWidth2(const double &wid2);
    virtual void setWidth(const double &wind);
    virtual void setSide(const double &len);
    
    virtual string getType() const;
    virtual void printInfo(ostream&) const;
};
Square::Square() : Rectangle(1, 1)
{}
Square::Square(const double &side) : Rectangle(side, side)
{}
Square::Square(const Square &s)
{
    this->setSide(s.getLength1());
}
double Square::getSide() const
{
    return this->getLength1();
}
void Square::setLength1(const double &len1)
{
    setSide(len1);
}
void Square::setLength2(const double &len2)
{
    setSide(len2);
}
void Square::setLength(const double &len)
{
    setSide(len);
}
void Square::setWidth1(const double &wid1)
{
    setSide(wid1);
}
void Square::setWidth2(const double &wid2)
{
    setSide(wid2);
}
void Square::setWidth(const double &wid)
{
    setSide(wid);
}
void Square::setSide(const double &len)
{
    this->Rectangle::setLength(len);
    this->Rectangle::setWidth(len);
}
string Square::getType() const
{
    return "Square";
}
void Square::printInfo(ostream &out) const
{
    out << setw(12) << getType() + ": ";
    out << "side = " << setprecision(2) << getSide() << ", ";
    out << "Area = " << setprecision(2) << getArea() << ", ";
    out << "Per. = " << setprecision(2) << getPerimeter();
}

class Node
{
typedef Node* NodePtr;
private:
    QuadPtr data;
    NodePtr link;
public:
    Node();
    Node(const QuadPtr &);
    Node(const Node &);
    ~Node();
    QuadPtr getData() const;
    NodePtr getLink() const;
    void setData(const QuadPtr &);
    void setLink(const NodePtr &);
    friend ostream& operator<< (ostream &, const Node &);
};
typedef Node* NodePtr;
Node::Node() : data(nullptr), link(nullptr) { }
Node::Node(const Node &n) : data(n.data), link(n.link){ }
Node::Node(const QuadPtr &d) : data(d), link(nullptr){ }
Node::~Node() { delete data; }
QuadPtr Node::getData() const { return data; }
NodePtr Node::getLink() const { return link; }
void Node::setData(const QuadPtr &d) { data = d; }
void Node::setLink(const NodePtr &p) { link = p; }
ostream& operator<< (ostream &out, const Node &n)
{
    out << *(n.data);
    return out;
}

class LinkedList
{
private:
    NodePtr head;
public:
    LinkedList();
    LinkedList(const LinkedList &);
    ~LinkedList();
    LinkedList& operator= (const LinkedList &);
    int getSize() const;
    void head_insert(const QuadPtr &);
    NodePtr search_node(const QuadPtr &) const;
    void insert_after(const NodePtr &, const QuadPtr &) const;
    void remove_node(const NodePtr &);
    void remove_node(const QuadPtr &);
    void remove_all(const QuadPtr &);
    void tail_insert(const QuadPtr &);
    void insert_before(const NodePtr &, const QuadPtr &);
    void insert_increasing(const QuadPtr &);
    void insert_grouped(const QuadPtr &);
    void insert_grouped_increasing(const QuadPtr &);
    friend ostream& operator<< (ostream &, const LinkedList &);
};
LinkedList::LinkedList() : head(nullptr) { }
LinkedList::LinkedList(const LinkedList &LL) : head(LL.head) { }
LinkedList::~LinkedList()
{
    NodePtr temp = head;
    while(head != nullptr)
    {
        temp = head;
        head = head->getLink();
        delete temp;
    }
}
LinkedList& LinkedList:: operator=(const LinkedList &LL)
{
    head = nullptr;
    NodePtr temp = LL.head;
    while (temp != nullptr)
    {
        NodePtr n = new Node(*temp);
        n->setLink(head);
        head = n;
        temp = temp->getLink();
    }
    return *this;
}
int LinkedList::getSize() const
{
    NodePtr temp = head;
    int count = 1;
    if (head == nullptr)
        return 0;
    else
    {
        while (temp->getLink() != nullptr)
        {
            temp = temp->getLink();
            count++;
        }
        return count;
    }
}
void LinkedList::head_insert(const QuadPtr &q)
{
    NodePtr n = new Node(q);
    n->setLink(head);
    head = n;
}
NodePtr LinkedList::search_node(const QuadPtr &q) const
{
    NodePtr temp = head;
    while (temp != nullptr)
    {
        if (temp->getData() == q)
            return temp;
        else
            temp = temp->getLink();
    }
    return nullptr;
}
void LinkedList::insert_after(const NodePtr &n, const QuadPtr &q) const
{
    if (n == nullptr)
        return;
    else
    {
        NodePtr temp = new Node(q);
        temp->setLink(n->getLink());
        n->setLink(temp);
    }
}
void LinkedList::remove_node(const NodePtr &n)
{
    if (head == nullptr || n == nullptr)
        return;
    else if (head == n)
    {
        head = head->getLink();
        delete n;
        return;
    }
    else
    {
        NodePtr b = head;
        while (b != nullptr)
        {
            if (b->getLink() == n)
            {
                b->setLink(n->getLink());
                delete n;
                return;;
            }
            b = b->getLink();
        }
    }
}
void LinkedList::remove_node(const QuadPtr &q)
{
    NodePtr n = search_node(q);
    remove_node(n);
}
void LinkedList::remove_all(const QuadPtr &q)
{
    NodePtr n;
    while(true)
    {
        n = search_node(q);
        if (n == nullptr)
            break;
        remove_node(n);
    }
}
void LinkedList::tail_insert(const QuadPtr &q)
{
    if (head == nullptr)
        head_insert(q);
    else
    {
        NodePtr b = head;
        while (b->getLink() != nullptr)
            b = b->getLink();
        insert_after(b, q);
    }
}
void LinkedList::insert_before(const NodePtr &n, const QuadPtr &q)
{
    if (head == nullptr)
    {
        if (n == nullptr)
            head_insert(q);
        else
            cout << "Insertion failed. Bad node argument." << endl;
    }
    else if (n == nullptr)
        tail_insert(q);
    else if (head == n)
        head_insert(q);
    else
    {
        NodePtr b = head;
        while (b!= nullptr)
        {
            if (b->getLink() == n)
                break;
            b = b->getLink();
        }
        if (b == nullptr)
            cout << "Insertion failed. Bad node argument." << endl;
        else
            insert_after(b, q);
    }
}
void LinkedList::insert_increasing(const QuadPtr &q)
{
    if (head == nullptr)
        head_insert(q);
    else
    {
        NodePtr temp = head;
        while (temp != nullptr)
        {
            if (temp->getData()->getPerimeter() > q->getPerimeter())
                break;
            else
                temp = temp->getLink();
        }
        insert_before(temp, q);
    }
    
}
void LinkedList::insert_grouped(const QuadPtr &q)
{
    if (head == nullptr)
        head_insert(q);
    else
    {
        NodePtr temp = head;
        NodePtr last;
        while (temp != nullptr)
        {
            if (temp->getData()->getType() == q->getType())
            {
                insert_before(temp, q);
                return;
            }
            if (temp->getData()->getType() == Square().getType())
                last = temp;
            temp = temp->getLink();
        }
        if (q->getType() == Square().getType())
            head_insert(q);
        else if (q->getType() == Rectangle().getType())
            insert_after(last, q);
        else
            tail_insert(q);
    }
}
void LinkedList::insert_grouped_increasing(const QuadPtr &q)
{
    if (head == nullptr)
        head_insert(q);
    else
    {
        bool checklist = false;
        NodePtr check = head;
        while (check != nullptr)
        {
            if (q->getType() == check->getData()->getType())
                checklist = true;
            check = check->getLink();
        }
        if (!checklist)
        {
            NodePtr last;
            NodePtr temp = head;
            while (temp != nullptr)
            {
                if (temp->getData()->getType() == Square().getType())
                    last = temp;
                temp = temp->getLink();
            }
            if (q->getType() == Square().getType())
                head_insert(q);
            else if (q->getType() == Rectangle().getType())
                insert_after(last, q);
            else
                tail_insert(q);
        }
        else
        {
            NodePtr temp_i = head;
            while (temp_i != nullptr)
            {
                if(temp_i->getData()->getType() == q->getType())
                    break;
                else
                    temp_i = temp_i->getLink();
            }
            NodePtr temp_j = temp_i;
            for( ; temp_j != nullptr; temp_j = temp_j->getLink())
                if(temp_j->getData()->getType() != q->getType())
                    break;
            NodePtr temp_k = temp_i;
            while(temp_k != temp_j)
            {
                if(temp_k->getData()->getArea() > q->getArea())
                    break;
                else
                    temp_k = temp_k->getLink();
            }
            insert_before(temp_k, q);
        }
    }
}
ostream& operator<< (ostream& out, const LinkedList& LL)
{
    NodePtr temp = LL.head;
    while(temp != nullptr)
    {
        out << *temp << endl;
        temp = temp->getLink();
    }
    return out;
}

/*****************************************************************************************************************************************************************************************************************
                                                         Work ENDS.
 
 
 
 
 
                                                        Test BELOW.
******************************************************************************************************************************************************************************************************************  */

//TEST LINKEDLIST
QuadPtr getRandomQuadrilateral()
{
    int r = rand() % 3;
    switch (r)
    {
        case 0:
            return new Trapezoid(rand()%5+1, rand()%5+1, rand()%5+1);
        case 1:
            return new Rectangle(rand()%5+1, rand()%5+1);
        default:
            return new Square(rand()%5+1);
    }
}
int main()
{
    //Let us use the same seed in order to generate the same random numbers on all the lab computers //that use the same version of MSVC++. This way the output of this program on computers with the //same Visual Studio 2010 compiler will be identical to the output provided below so long as your //implementations are correct.
    unsigned int seed = 0;
    srand(seed); //Normally srand(time(0)) should be used for rigorous testing
    const int SIZE = rand() % 6 + 25;
    //Declare a linkedlist container to store pointers to Shape objects
    LinkedList LL;
    //Print the number of objects at the beginning
    cout << "At the beginning there are " << Quadrilateral::getCount() << " objects constructed." << endl;
    cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
    ///////////////////////////////////// TASK 1 ///////////////////////////////////////////////////////  //Insert SIZE random objects into the linked list container using insert_increasing member function
    cout << endl << "Inserting " << SIZE << " objects with insert_increasing member function" << endl;
    cout << "***********************************************************" << endl;
    for (int i = 0; i < SIZE; i++) {
        QuadPtr p = getRandomQuadrilateral();
        cout << "Inserting " << endl << *p << endl;
        LL.insert_increasing(p);
    }
    //Print the number of objects constructed so far and the number of elements of the linked list container
    cout << endl << "Now there are " << Quadrilateral::getCount() << " objects constructed." << endl;
    cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
    //Print the elements of the linked list container
    cout << "The elements of the linkedlist container are" << endl;
    cout << LL << endl;
    //Now delete all the elements of the linked list container and also clear the linked list container
    cout << endl << "Emptying the linkedlist container." << endl;
    LL.~LinkedList();
    //Print the number of objects we still have in our application and in the linked list container
    cout << "Now there are " << Quadrilateral::getCount() << " objects constructed." << endl;
    cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
    ///////////////////////////////////// TASK 2 /////////////////////////////////////////////////////// //Insert SIZE random objects into the linked list container using insert_grouped function
    cout << "Inserting " << SIZE << " objects with insert_grouped function" << endl;
    cout << "*************************************************" << endl;
    for (int i = 0; i < SIZE; i++) {
        QuadPtr p = getRandomQuadrilateral();
        cout << "Inserting " << endl << *p << endl;
        LL.insert_grouped(p);
    }
    //Print the number of objects constructed so far and the number of elements of the linked list container
    cout << endl << "Now there are " << Quadrilateral::getCount() << " objects constructed." << endl;
    cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
    //Print the elements of the linked list container
    cout << "The elements of the linkedlist container are" << endl;
    cout << LL << endl;
    //Now delete all the elements of the linked list container and also clear the linked list container
    cout << endl << "Emptying the linkedlist container." << endl;
    LL.~LinkedList();
    //Print the number of objects we still have in our application and in the linked list container
    cout << "Now there are " << Quadrilateral::getCount() << " objects constructed." << endl;
    cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
    ///////////////////////////////////// TASK 3 /////////////////////////////////////////////////////// //Insert SIZE random objects into the container using insert_grouped_increasing function
    cout << "Inserting " << SIZE << " objects with insert_grouped_increasing function" << endl;
    cout << "************************************************************" << endl;
    for (int i = 0; i < SIZE; i++) {
        QuadPtr p = getRandomQuadrilateral();
        cout << "Inserting " << endl << *p << endl; LL.insert_grouped_increasing(p);
    }
    //Print the number of objects constructed so far and the number of elements of the linked list container
    cout << endl << "Now there are " << Quadrilateral::getCount() << " objects constructed." << endl; cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
    //Print the elements of the linked list container
    cout << "The elements of the linkedlist container are" << endl; cout << LL << endl;
    //Now delete all the elements of the linked list container and also clear the linked list container
    cout << endl << "Emptying the linkedlist container." << endl; LL.~LinkedList();
    //Print the number of objects we still have in our application and in the linked list container
    cout << "Now there are " << Quadrilateral::getCount() << " objects constructed." << endl;
    cout << "And there are " << LL.getSize() << " elements in the linkedlist container." << endl << endl;
    system("Pause");
    return 0;
}





//TEST Q.. CLASS
/*int main()
{
    cout << "Testing Trapezoid behaviour..." << endl;
    Trapezoid t;
    cout << "Default Trapezoid object" << endl;
    cout << "\tlength1 = " << t.getLength1() << ", ";    cout << "length2 = " << t.getLength2() << ", ";
    cout << "width1 = " << t.getWidth1() << ", ";        cout << "width2 = " << t.getWidth2() << ", ";
    cout << "width = " << t.getWidth() << endl;
    cout << endl;

    t.setLength1(5);
    cout << "Length1 modified" << endl;
    cout << "\tlength1 = " << t.getLength1() << ", ";    cout << "length2 = " << t.getLength2() << ", ";
    cout << "width1 = " << t.getWidth1() << ", ";        cout << "width2 = " << t.getWidth2() << ", ";
    cout << "width = " << t.getWidth() << endl;
    cout << endl;

    t.setLength2(6);
    cout << "Length2 modified" << endl;
    cout << "\tlength1 = " << t.getLength1() << ", ";    cout << "length2 = " << t.getLength2() << ", ";
    cout << "width1 = " << t.getWidth1() << ", ";        cout << "width2 = " << t.getWidth2() << ", ";
    cout << "width = " << t.getWidth() << endl;
    cout << endl;

    t.setWidth1(7);
    cout << "Width1 modified" << endl;
    cout << "\tlength1 = " << t.getLength1() << ", ";    cout << "length2 = " << t.getLength2() << ", ";
    cout << "width1 = " << t.getWidth1() << ", ";        cout << "width2 = " << t.getWidth2() << ", ";
    cout << "width = " << t.getWidth() << endl;
    cout << endl;

    t.setWidth2(8);
    cout << "Width2 modified" << endl;
    cout << "\tlength1 = " << t.getLength1() << ", ";    cout << "length2 = " << t.getLength2() << ", ";
    cout << "width1 = " << t.getWidth1() << ", ";        cout << "width2 = " << t.getWidth2() << ", ";
    cout << "width = " << t.getWidth() << endl;
    cout << endl;

    t.setWidth(4);
    cout << "Width modified" << endl;
    cout << "\tlength1 = " << t.getLength1() << ", ";    cout << "length2 = " << t.getLength2() << ", ";
    cout << "width1 = " << t.getWidth1() << ", ";        cout << "width2 = " << t.getWidth2() << ", ";
    cout << "width = " << t.getWidth() << endl;
    cout << endl;

    cout << "Testing Rectangle behaviour..." << endl;
    Rectangle r;
    cout << "Default Rectangle object" << endl;
    cout << "\tlength1 = " << r.getLength1() << ", ";    cout << "length2 = " << r.getLength2() << ", ";
    cout << "width1 = " << r.getWidth1() << ", ";        cout << "width2 = " << r.getWidth2() << ", ";
    cout << "length = " << r.getLength() << ", ";        cout << "width = " << r.getWidth() << endl;
    cout << endl;

    r.setLength1(5);
    cout << "Length1 modified" << endl;
    cout << "\tlength1 = " << r.getLength1() << ", ";    cout << "length2 = " << r.getLength2() << ", ";
    cout << "width1 = " << r.getWidth1() << ", ";        cout << "width2 = " << r.getWidth2() << ", ";
    cout << "length = " << r.getLength() << ", ";        cout << "width = " << r.getWidth() << endl;
    cout << endl;

    r.setLength2(6);
    cout << "Length2 modified" << endl;
    cout << "\tlength1 = " << r.getLength1() << ", ";    cout << "length2 = " << r.getLength2() << ", ";
    cout << "width1 = " << r.getWidth1() << ", ";        cout << "width2 = " << r.getWidth2() << ", ";
    cout << "length = " << r.getLength() << ", ";        cout << "width = " << r.getWidth() << endl;
    cout << endl;

    r.setWidth1(7);
    cout << "Width1 modified" << endl;
    cout << "\tlength1 = " << r.getLength1() << ", ";    cout << "length2 = " << r.getLength2() << ", ";
    cout << "width1 = " << r.getWidth1() << ", ";        cout << "width2 = " << r.getWidth2() << ", ";
    cout << "length = " << r.getLength() << ", ";        cout << "width = " << r.getWidth() << endl;
    cout << endl;

    r.setWidth2(8);
    cout << "Width2 modified" << endl;
    cout << "\tlength1 = " << r.getLength1() << ", ";    cout << "length2 = " << r.getLength2() << ", ";
    cout << "width1 = " << r.getWidth1() << ", ";        cout << "width2 = " << r.getWidth2() << ", ";
    cout << "length = " << r.getLength() << ", ";        cout << "width = " << r.getWidth() << endl;
    cout << endl;

    r.setLength(3);
    cout << "Length modified" << endl;
    cout << "\tlength1 = " << r.getLength1() << ", ";    cout << "length2 = " << r.getLength2() << ", ";
    cout << "width1 = " << r.getWidth1() << ", ";        cout << "width2 = " << r.getWidth2() << ", ";
    cout << "length = " << r.getLength() << ", ";        cout << "width = " << r.getWidth() << endl;
    cout << endl;

    r.setWidth(4);
    cout << "Width modified" << endl;
    cout << "\tlength1 = " << r.getLength1() << ", ";    cout << "length2 = " << r.getLength2() << ", ";
    cout << "width1 = " << r.getWidth1() << ", ";        cout << "width2 = " << r.getWidth2() << ", ";
    cout << "length = " << r.getLength() << ", ";        cout << "width = " << r.getWidth() << endl;
    cout << endl;

    cout << "Testing Square behaviour..." << endl;
    Square s;
    cout << "Default Square object" << endl;
    cout << "\tlength1 = " << s.getLength1() << ", ";    cout << "length2 = " << s.getLength2() << ", ";
    cout << "width1 = " << s.getWidth1() << ", ";        cout << "width2 = " << s.getWidth2() << ", ";
    cout << "length = " << s.getLength() << ", ";        cout << "width = " << s.getWidth() << ", ";
    cout << "side = " << s.getSide() << endl;
    cout << endl;

    s.setLength1(4);
    cout << "Length1 modified" << endl;
    cout << "\tlength1 = " << s.getLength1() << ", ";    cout << "length2 = " << s.getLength2() << ", ";
    cout << "width1 = " << s.getWidth1() << ", ";        cout << "width2 = " << s.getWidth2() << ", ";
    cout << "length = " << s.getLength() << ", ";        cout << "width = " << s.getWidth() << ", ";
    cout << "side = " << s.getSide() << endl;
    cout << endl;

    s.setLength2(5);
    cout << "Length2 modified" << endl;
    cout << "\tlength1 = " << s.getLength1() << ", ";    cout << "length2 = " << s.getLength2() << ", ";
    cout << "width1 = " << s.getWidth1() << ", ";        cout << "width2 = " << s.getWidth2() << ", ";
    cout << "length = " << s.getLength() << ", ";        cout << "width = " << s.getWidth() << ", ";
    cout << "side = " << s.getSide() << endl;
    cout << endl;

    s.setWidth1(6);
    cout << "Width1 modified" << endl;
    cout << "\tlength1 = " << s.getLength1() << ", ";    cout << "length2 = " << s.getLength2() << ", ";
    cout << "width1 = " << s.getWidth1() << ", ";        cout << "width2 = " << s.getWidth2() << ", ";
    cout << "length = " << s.getLength() << ", ";        cout << "width = " << s.getWidth() << ", ";
    cout << "side = " << s.getSide() << endl;
    cout << endl;

    s.setWidth2(7);
    cout << "Width2 modified" << endl;
    cout << "\tlength1 = " << s.getLength1() << ", ";    cout << "length2 = " << s.getLength2() << ", ";
    cout << "width1 = " << s.getWidth1() << ", ";        cout << "width2 = " << s.getWidth2() << ", ";
    cout << "length = " << s.getLength() << ", ";        cout << "width = " << s.getWidth() << ", ";
    cout << "side = " << s.getSide() << endl;
    cout << endl;

    s.setLength(2);
    cout << "Length modified" << endl;
    cout << "\tlength1 = " << s.getLength1() << ", ";    cout << "length2 = " << s.getLength2() << ", ";
    cout << "width1 = " << s.getWidth1() << ", ";        cout << "width2 = " << s.getWidth2() << ", ";
    cout << "length = " << s.getLength() << ", ";        cout << "width = " << s.getWidth() << ", ";
    cout << "side = " << s.getSide() << endl;
    cout << endl;

    s.setWidth(3);
    cout << "Width modified" << endl;
    cout << "\tlength1 = " << s.getLength1() << ", ";    cout << "length2 = " << s.getLength2() << ", ";
    cout << "width1 = " << s.getWidth1() << ", ";        cout << "width2 = " << s.getWidth2() << ", ";
    cout << "length = " << s.getLength() << ", ";        cout << "width = " << s.getWidth() << ", ";
    cout << "side = " << s.getSide() << endl;
    cout << endl;

    s.setSide(2);
    cout << "Side modified" << endl;
    cout << "\tlength1 = " << s.getLength1() << ", ";    cout << "length2 = " << s.getLength2() << ", ";
    cout << "width1 = " << s.getWidth1() << ", ";        cout << "width2 = " << s.getWidth2() << ", ";
    cout << "length = " << s.getLength() << ", ";        cout << "width = " << s.getWidth() << ", ";
    cout << "side = " << s.getSide() << endl;
    cout << endl;

    //Test Polymorphism. Construct few objects on the heap and place them in a container
    srand(time(0));
    const int size = rand() % 10 + 5;
    Quadrilateral **v = new Quadrilateral*[size];
    for (int i = 0; i < size; i++)
    {
        if (i % 3 == 0)
            v[i] = new Trapezoid(3*(1.0*rand()/RAND_MAX), 3*(1.0*rand()/RAND_MAX), 3*(1.0*rand()/RAND_MAX));
        else if (i % 3 == 1)
            v[i] = new Rectangle(3*(1.0*rand()/RAND_MAX), 3*(1.0*rand()/RAND_MAX));
        else
            v[i] = new Square(3*(1.0*rand()/RAND_MAX));
    }
    cout << "The elements of the array are..." << endl;
    for (int i = 0; i < size; i++)
        cout << "Element at index " << i << " is " << endl << *(v[i]) << endl << endl;

    //Destruct the objects on the heap
    for (int i = 0; i < size; i++)
        delete v[i];

    //Clean up heap memory
    delete[] v;
    
    system("Pause");
    return 0;
}
*/
