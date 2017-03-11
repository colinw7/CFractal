#include <CQXmlMandelbrot.h>
#include <CQMandelbrot.h>
#include <CQXml.h>
#include <QApplication>

const char dialogXml[] = "\
<qxml>\n\
<QFrame>\n\
<QHBoxLayout>\n\
<CQMandelbrot name=\"mandelbrot\"/>\n\
<CQPropertyTree fixedWidth=\"300\">\n\
<CQPropertyItem propertyName=\"threaded\" propertyWidget=\"mandelbrot\"/>\n\
<CQPropertyItem propertyName=\"iterations\" propertyWidget=\"mandelbrot\"/>\n\
<CQPropertyItem propertyName=\"showVector\" propertyWidget=\"mandelbrot\"/>\n\
<CQPropertyItem propertyName=\"range\" propertyWidget=\"mandelbrot\"/>\n\
</CQPropertyTree>\n\
</QHBoxLayout>\n\
</QFrame>\n\
</qxml>";

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQXmlMandelbrot mandelbrot;

  mandelbrot.setGeometry(10, 10, 800, 500);

  mandelbrot.show();

  return app.exec();
}

CQXmlMandelbrot::
CQXmlMandelbrot()
{
  CQXml xml;

  CQXmlAddWidgetFactoryT(&xml, CQMandelbrot);

  xml.createWidgetsFromString(this, dialogXml);
}
