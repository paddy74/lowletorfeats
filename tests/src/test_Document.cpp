#include <lowletorfeats/base/Document.hpp>

int main()
{
    // Test constructors
    lowletorfeats::StructuredDocument doc =
        lowletorfeats::StructuredDocument();
    doc = lowletorfeats::StructuredDocument(doc);

    // Test public methods
    doc.toString();
    doc.clear();
    doc.clearSection("full");
    doc.clearFeatureMap();

    // doc.getDocLen();
    // doc.getDocLen("full");

    doc.getStructuredTermFrequencyMap();
    // doc.getTermFrequencyMap();
    // doc.getTermFrequencyMap("full");

    // doc.getMaxTF();
    // doc.getMaxTF("full");

    doc.getFeatureMap();
    doc.getFeatureKeys();
    // doc.getFeatureValue(fKey);
    doc.getFeatureVector();
    // doc.updateFeature(fKey, fValue);

    return 0;
}
