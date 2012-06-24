#include "solvencia.h"

Solvencia::Solvencia(QWidget *parent) :
        QWidget(parent)
{

}

void Solvencia::initGUI(QWidget *central)
{
    lblCedula = new QLabel(central);
    lblCedula->setText("Ingrese C�dula: ");
    lblCedula->setFont(QFont("Baskerville Old Face",12,QFont::Bold));
    lblCedula->move(QPoint(335,140));
    lblCedula->setVisible(false);

    lineEditCedula = new QLineEdit(central);
    lineEditCedula->setValidator(new QIntValidator(1,99999999,this));
    lineEditCedula->move(QPoint(465,140));
    lineEditCedula->setVisible(false);

    btnSolvencia = new QPushButton(central);
    btnSolvencia->setText("&Generar");
    btnSolvencia->move(QPoint(425,180));
    btnSolvencia->setVisible(false);
    connect(btnSolvencia, SIGNAL(clicked()), this, SLOT(slotGenerateSolvencia()));

}

void Solvencia::slotGenerateSolvencia()
{

    if( lineEditCedula->text().isEmpty() ) {
        QMessageBox::warning(this, "Advertencia", "No debe dejar campos vacios.");
        return;
    }

    QString strQuery = "SELECT * FROM libroPersona WHERE cedulaFk = " + lineEditCedula->text();

    qDebug() << strQuery;

    query.exec(strQuery);

    if( !query.next() ) {

        QPrinter printer(QPrinter::HighResolution);
        printer.setPageSize(QPrinter::Letter);
        printer.setOrientation(QPrinter::Portrait);
        printer.setPaperSource(QPrinter::Tractor);

        QPrintDialog dialog(&printer, this);
        dialog.setWindowTitle("Imprimir Documento");

        if( dialog.exec() != QDialog::Accepted )
            return;

        printDocument(&printer);

        visibleWidget(false);

    } else {
        QMessageBox::warning(this, "Advertencia", "El usuario tiene libros en pr�stamo.");
        return;
    }

}

QList<QString> Solvencia::cuadroTitulo()
{
    QList<QString> listString;
    QString titulo = "Rep�blica Bolivariana de Venezuela";
    listString.append(titulo);

    titulo = "ESCUELA BASICA NACIONAL \"ELOY PAREDES\"";
    listString.append(titulo);
    titulo = "M�RIDA ESTADO M�RIDA";
    listString.append(titulo);

    return listString;
}

QString Solvencia::cuadroConstancia()
{
    QString constancia = "El personal de la Biblioteca \"INES OTILLA FERNANDEZ\", que funciona en la Escuela ";
    constancia += "B�sica \"Eloy Paredes\", en la Urbanizaci�n Humboldt, Municipio Aut�nomo Libertador de ";
    constancia += "la Parroquia Caracciolo Parra P�rez del estado M�rida.";

    return constancia;
}

QString Solvencia::cuadroConstar1()
{

    QString constar = "Que _______________________________________, alumno (a) titular de la C�dula de ";
    constar += "Indentidad N� ______________________, del _______________________ de Educaci�n ";
    constar += "B�sica, A�o Escolar _______________, se encuentra solvente en esta Biblioteca.";

    return constar;
}

QString Solvencia::cuadroConstar2()
{
    QString constar = "Constancia que se expide a solicitud de parte interesada para los fines legales ";
    constar += "consiguientes en la ciudad de M�rida, a los _______ d�as del mes de ________________ ";
    constar += "del a�o ____________.";

    return constar;
}

void Solvencia::printDocument(QPrinter *printer)
{

    QList<QString> listHtml = cuadroTitulo();

    QPainter painter(printer);

    painter.setFont(QFont("Arial", 10, QFont::Bold));

    // TITULO
    painter.drawText(370, 370, 2000, 100, Qt::AlignLeft
                     | Qt::TextWordWrap, listHtml.at(0));
    QImage img;
    img.load(":images/melogo.png");
    painter.drawImage(370,500,img);

    painter.drawText(370, 780, 2000, 100, Qt::AlignLeft
                     | Qt::TextWordWrap, listHtml.at(1));
    painter.drawText(370, 910, 2000, 100, Qt::AlignLeft
                     | Qt::TextWordWrap, listHtml.at(2));

    QString html;

    // CONSTANCIA
    html = cuadroConstancia();
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(1550, 1650, 2000, 100, Qt::AlignCenter
                     | Qt::TextWordWrap, "CONSTANCIA");

    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(370, 1990, 4200, 360, Qt::AlignJustify
                     | Qt::TextWordWrap, html);

    // HACE CONSTAR
    html = cuadroConstar1();
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(1550, 2700, 2000, 100, Qt::AlignCenter
                     | Qt::TextWordWrap, "HACER CONSTAR");

    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(370, 3040, 4200, 390, Qt::AlignJustify
                     | Qt::TextWordWrap, html);
    // AQUI AGREGAR DATA

    html = cuadroConstar2();
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(370, 3670, 4200, 390, Qt::AlignJustify
                     | Qt::TextWordWrap, html);
    // AQUI AGREGAR DATA

    // SELLO Y FIRMA
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(685, 5260, 1000, 100, Qt::AlignJustify
                     | Qt::TextWordWrap, "SELLO");
    painter.drawText(2500, 5260, 4000, 110, Qt::AlignJustify
                     | Qt::TextWordWrap, "______________________________");
    painter.drawText(2980, 5380, 4000, 100, Qt::AlignJustify
                     | Qt::TextWordWrap, "BIBLIOTECARIO");

}

void Solvencia::visibleWidget(bool visible)
{
    lblCedula->setVisible(visible);
    lineEditCedula->setVisible(visible);
    lineEditCedula->setText("");

    btnSolvencia->setVisible(visible);
}






