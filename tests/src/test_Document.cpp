#include <lowletorfeats/base/Document.hpp>

int main()
{
    // Test constructors
    lowletorfeats::StructuredDocument doc =
        lowletorfeats::StructuredDocument();
    doc = lowletorfeats::StructuredDocument(doc);

    // Test public methods

    return 0;
}
