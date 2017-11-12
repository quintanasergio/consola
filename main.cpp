#include <QCoreApplication>
#include <QTextStream>
#include <QProcess>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream qout(stdout);
    QByteArray result;
    QProcess cmd2;

    cmd2.setReadChannel(QProcess::StandardOutput);
    cmd2.setProcessChannelMode(QProcess::MergedChannels);
    cmd2.start("bash");
    if (!cmd2.waitForStarted()){
        qout << "Error: Could not start!" << endl;
        return 0;
    }

    QStringList args = a.arguments();
    qout << endl << "---Simulando----" << endl;
    cmd2.write("cd /home/sergio/Documentos/simulador-arap-v1.0-master\n");
    QString towrite;
    towrite = "make PARAMETROS=\""+args[1]+".txt\" RUNS=" +args[2]+ " run\n";
    qout << towrite << endl;
    cmd2.write(towrite.toLatin1().data());
    cmd2.write("cd arap-dir\n");
    cmd2.write("mkdir -p Experiments\n");
    cmd2.write("cd Experiments\n");
    towrite = "mkdir -p "+ args[1] +"\n";
    cmd2.write(towrite.toLatin1().data());
    towrite = "cd "+ args[1] +"\n";
    cmd2.write(towrite.toLatin1().data());
    cmd2.write("mkdir -p load-ants-model\n");
    cmd2.write("mkdir -p load-ants-paths\n");
    cmd2.write("mkdir -p tablas\n");

    cmd2.write("cd ../..\n");
    towrite = "mv ./load-ants-model/* ./Experiments/"+args[1]+"/load-ants-model/\n";
    cmd2.write(towrite.toLatin1().data());

    towrite = "mv ./load-ants-paths/* ./Experiments/"+args[1]+"/load-ants-paths/\n";
    cmd2.write(towrite.toLatin1().data());

    towrite = "mv ./tablas/* ./Experiments/"+args[1]+"/tablas/\n";
    cmd2.write(towrite.toLatin1().data());

    towrite = "mv "+args[1]+".txt ./Experiments/"+args[1]+"/\n";
    cmd2.write(towrite.toLatin1().data());

    towrite = "mv *.log ./Experiments/"+args[1]+"/\n";
    cmd2.write(towrite.toLatin1().data());

    cmd2.write("cd ../../../Projects/build-arapResults-Desktop_Qt_5_7_0_GCC_64bit-Debug/\n");

    towrite = "./arapResults "+args[1]+ "\n";
    cmd2.write(towrite.toLatin1().data());

    cmd2.closeWriteChannel();   //done Writing

    while(cmd2.state()!=QProcess::NotRunning){
        cmd2.waitForReadyRead();
        result = cmd2.readAll();
        qout << result;
    }
    qout << endl << "---Fin----" << endl;


//    return a.exec();
//    a.quit();
}
