#include "Expression.hpp"

// ostream & operator << (ostream & out, Expression * e )
// {
//     e->affiche(out);
//     return out;
// }

ostream& operator<<( ostream& out, Expression const & e )
{
        e.affiche(out);
        return out;
}