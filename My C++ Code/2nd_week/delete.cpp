void Polynomial::insertTerm(const Term &term)
{
    if (term.coeff == 0)
        return;

    if (this->terms->size() == 0)
    {
        this->terms->add(term);
    }
    else
    {
        int i = 0, n = this->terms->size();
        for (i = 0; i < n; i++)
        {
            Term temp = this->terms->get(i);
            if (temp.exp > term.exp)
            {
                continue;
            }
            else
            {
                if (temp.exp < term.exp)
                {
                    this->terms->add(i, term);
                    break;
                }
                else
                {
                    Term replaceTerm(temp.coeff + term.coeff, term.exp);
                    if (temp.coeff + term.coeff == 0)
                        this->terms->removeAt(i);
                    else
                        this->terms->set(i, replaceTerm);
                    break;
                }
            }
        }
        if (i == n)
            this->terms->add(term);
    }
}

void Polynomial::insertTerm(double coeff, int exp)
{
    Term term(coeff, exp);
    this->insertTerm(term);
}