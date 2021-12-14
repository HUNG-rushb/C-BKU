#include "SLinkedList.h"
using namespace std;

class Polynomial;

class Term
{
private:
    double coeff;
    int exp;
    friend class Polynomial;

public:
    // Constructor
    Term(double coeff = 0.0, int exp = 0)
    {
        this->coeff = coeff;
        this->exp = exp;
    }

    // So sanh 2 term voi nhau
    bool operator==(const Term& rhs) const
    {
        return (this->coeff == rhs.coeff && this->exp == rhs.exp);
    }

    // Operator <<
    friend ostream & operator<<(ostream &os, const Term& term)
    {
        cout << endl;
        cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};


//Points to keep in Mind while working with Polynomials:
//- The sign of each coefficient and exponent
//    is stored within the coefficient and the exponent itself.
//- The storage allocation for each term in the polynomial must be done
//    in descending order of their exponent.
class Polynomial
{
private:
    // Danh sach lien ket don voi kieu du lieu Terms
    // terms la SLL
    SLinkedList<Term> *terms;

public:
    // Constructor
    Polynomial()
    {
        this->terms = new SLinkedList<Term>();
    }

    // Destructor
    ~Polynomial()
    {
        this->terms->clear();
    }

    // Insert term
    void insertTerm(const Term& term);
    void insertTerm(double coeff, int exp);

    // Polynomial operator+(const Polynomial& rhs);

    // Print
    void print()
    {
        SLinkedList<Term>::Iterator it;
        cout << "[";

        for (it = this->terms->begin(); it != this->terms->end(); it++)
        {
            cout << (*it);
        }

        cout << endl << "]";
    }
};


//void Polynomial::insertTerm(const Term& term)
//{
//    // COEFF la he so
//    // EXP la so mu
//
//    // List is empty
//    if (this->term->size() == 0)
//    {
//        this->terms->add(term);
//    }
//    else
//    {
//        SLinkedList<Term>::Node currentTerm =  new SLinkedList<Term>::Node;
//        currentTerm = this->terms->head; // head ???
//
//        if (term.exp > 0)
//        {
//            int countIndex = 0;
//            while(this->terms->get(countIndex).exp != term.exp - 1 )
//            {
//                countIndex += 1;
//            }
//
//            this->terms->add(countIndex, term);
//
//        }
//    }
//
//    SLinkedList<Term>::Iterator currentNode =  new SLinkedList<Term>::Iterator;
//    currentNode = this->terms->begin();
//}

void Polynomial::insertTerm(const Term &term)
{
    // HE SO bang 0
    if (term.coeff == 0)
        return;

    // List Terms dang empty
    if (this->terms->size() == 0)
    {
        this->terms->add(term);
    }
    // List Terms ko empty
    else
    {
        int currentEXP = 0;
        int totalEXP = this->terms->size();

        // vong lap de update List term
        for (currentEXP = 0; currentEXP < totalEXP; currentEXP++)
        {
            // Truy cap vao data kieu Term tai node i
            // get tra ve data
            Term currentTemrNode = this->terms->get(currentEXP);

            /******************************************
            *           ...8 7 6 5 4 3 2 1 0          *
            ******************************************/

            // Neu nhu so mu hien tai > so mu truyen vao
            // tiep tuc vong lap for
            if (currentTemrNode.exp > term.exp)
            {
                continue;
            }
            else
            {
                // Neu nhu so mu hien tai < so mu truyen vao
                // thi ta them terms vao vi tri currentEXP
                if (currentTemrNode.exp < term.exp)
                {
                    this->terms->add(currentEXP, term);
                    break;
                }
                // Neu nhu so mu hien tai = so mu truyen vao
                else
                {
                    // Tao ra 1 term node moi
                    Term replaceTerm(currentTemrNode.coeff + term.coeff, term.exp);

                    // Neu nhu he so tao ra bang 0
                    // xoa node tai vi tri currentEXP
                    if (currentTemrNode.coeff + term.coeff == 0)
                        this->terms->removeAt(currentEXP);

                    // Neu tao ra so != 0
                    // thay the term tai vi tri node currentEXP bang term moi voi data moi
                    // coeff va exp
                    else
                        this->terms->set(currentEXP, replaceTerm);

                    // thoat khoi vong lap
                    break;
                }
            }
        }

        // Them vao cuoi
        // So mu truyen vao la be nhat
        if (currentEXP == totalEXP)
            this->terms->add(term);
    }
}

void Polynomial::insertTerm(double coeff, int exp)
{
    // Tao ra term node moi
    Term term(coeff, exp);

    // Su dung lai insert(const *term)
    this->insertTerm(term);
}

int main()
{
    Polynomial *poly = new Polynomial();
    poly->insertTerm(6.0, 2);
    poly->insertTerm(4.0, 5);
    poly->insertTerm(6.0, 5);
    poly->insertTerm(-1.0, 0);

    poly->insertTerm(4.0, 3);


    poly->insertTerm(-6.0, 6);
    poly->insertTerm(6.0, 6);
    poly->print();

    return 0;
}
