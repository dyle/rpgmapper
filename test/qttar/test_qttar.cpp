#include <QtCore>

#define ENABLE_HIDDEN_FILE_INFO_STRUCTURE
#include <QtTAR/QtTAR>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

#include <rpgmapper/common_macros.h>


class TarBALL : public QtTarBall
{
  public:

    explicit     TarBALL     (void) ;
    virtual     ~TarBALL     (void) ;

  protected:

    virtual bool Interval    (void) ;
    virtual void Report      (void * hiddenFileInfo) ;

    virtual bool setFileMode (QDir root,QIODevice & IO,void * hiddenFileInfo) ;

  private:

} ;

void nprintf(QString message,bool lf,bool cr)
{
  QTextCodec * codec = QTextCodec::codecForLocale() ;
  QByteArray   M     = codec->fromUnicode(message)  ;
  int          L     = M . size ( )                 ;
  ///////////////////////////////////////////////////
  if ( L <= 0 )                                     {
    if (lf || cr)                                   {
      char f [ 64 ]                                 ;
      ::strcpy         ( f    , ""    )             ;
      if (cr) ::strcat ( f    , "\r"  )             ;
      if (lf) ::strcat ( f    , "\n"  )             ;
      ::printf         ( "%s" , f     )             ;
    }                                               ;
    return                                          ;
  }                                                 ;
  ///////////////////////////////////////////////////
  char * p = new char[L+16]                         ;
  memset   ( p , 0        , L+16 )                  ;
  memcpy   ( p , M.data() , L    )                  ;
  if (lf || cr)                                     {
    char f [ 64 ]                                   ;
    ::strcpy         ( f , ""      )                ;
    if (cr) ::strcat ( f , "\r"    )                ;
    if (lf) ::strcat ( f , "\n"    )                ;
    ::strcat         ( p , f       )                ;
  }                                                 ;
  ::printf           ( "%s" , p    )                ;
  delete [] p                                       ;
}


TarBALL:: TarBALL   (void)
        : QtTarBall (    )
{
}

TarBALL::~TarBALL (void)
{
}

bool TarBALL::Interval(void)
{
  return true ;
}

void TarBALL::Report(void * hiddenFileInfo)
{
  HiddenFileInfo * hfi = (HiddenFileInfo *) hiddenFileInfo ;
  nprintf ( hfi -> Filename , true , true )                ;
}

bool TarBALL::setFileMode(UNUSED QDir root, UNUSED QIODevice & IO,UNUSED void * hiddenFileInfo)
{
  UNUSED HiddenFileInfo * hfi = (HiddenFileInfo *) hiddenFileInfo ;
  return true                                              ;
}

QStringList ToArgs(int argc,char ** argv)
{
  QTextCodec * codec = QTextCodec::codecForLocale ( ) ;
  QStringList  s                                      ;
  for (int i = 0 ; i < argc ; i++ )                   {
    s << codec -> toUnicode ( argv [ i ] )            ;
  }                                                   ;
  return s                                            ;
}

bool LoadAll(QString filename,QByteArray & data)
{
  QFile F ( filename )                                   ;
  if ( ! F . open ( QIODevice::ReadOnly ) ) return false ;
  data = F . readAll ( )                                 ;
  F . close ( )                                          ;
  return true                                            ;
}

bool SaveAll(QString filename,QByteArray & data)
{
  QFile F ( filename )                                   ;
  if ( ! F . open ( QIODevice::WriteOnly                 |
                    QIODevice::Truncate ) ) return false ;
  F . write ( data )                                     ;
  F . close (      )                                     ;
  return true                                            ;
}

void Help (void)
{
  nprintf("List    : tartool -l -t input.tar"           ,true,true) ;
  nprintf("Extract : tartool -e -t input.tar -d rootdir",true,true) ;
  nprintf("Archive : tartool -a -t input.tar -d rootdir",true,true) ;
}

void ListTarBall(QString filename)
{
  QDir    d = QDir::current ( )   ;
  TarBALL tarball                 ;
  tarball . List ( d , filename ) ;
}

void ExtractTarBall(QString filename,QDir root)
{
  TarBALL tarball                       ;
  tarball . Extract ( root , filename ) ;
}

void MakeTarBall(QString filename,QDir src)
{
  TarBALL tarball                             ;
  QDir    root = QDir::current ( )            ;
  tarball . TarBall ( filename , root , src ) ;
}

int Interpret(QStringList cmds)
{
  if ( cmds . count ( ) < 2 )                      {
    Help ( )                                       ;
    return 1                                       ;
  }                                                ;
  int     ioa = -1                                 ;
  //////////////////////////////////////////////////
  cmds . takeAt ( 0 )                              ;
  if ( "-l" == cmds [ 0 ] )                        {
    ioa = 1                                        ;
  }                                                ;
  if ( "-e" == cmds [ 0 ] )                        {
    ioa = 2                                        ;
  }                                                ;
  if ( "-a" == cmds [ 0 ] )                        {
    ioa = 3                                        ;
  }                                                ;
  if ( ( ioa < 1 ) || ( ioa > 3 ) )                {
    Help ( )                                       ;
    return 1                                       ;
  }                                                ;
  //////////////////////////////////////////////////
  QString tfile   = ""                             ;
  QString rootdir = ""                             ;
  cmds . takeAt ( 0 )                              ;
  while ( cmds . count ( ) > 0 )                   {
    if ( "-t" == cmds [ 0 ] )                      {
      cmds . takeAt ( 0 )                          ;
      if ( cmds . count ( ) > 0 )                  {
        tfile = cmds [ 0 ]                         ;
        cmds . takeAt ( 0 )                        ;
      } else                                       {
        Help ( )                                   ;
        return 1                                   ;
      }                                            ;
    } else
    if ( "-d" == cmds [ 0 ] )                      {
      cmds . takeAt ( 0 )                          ;
      if ( cmds . count ( ) > 0 )                  {
        rootdir = cmds [ 0 ]                       ;
        cmds . takeAt ( 0 )                        ;
      } else                                       {
        Help ( )                                   ;
        return 1                                   ;
      }                                            ;
    } else
    if ( cmds . count ( ) > 0 )                    {
      cmds . takeAt ( 0 )                          ;
    }                                              ;
  }                                                ;
  //////////////////////////////////////////////////
  switch ( ioa )                                   {
    case 1                                         :
    case 2                                         :
    case 3                                         :
      if ( ( tfile.length ( ) <= 0 ) )             {
        Help ( )                                   ;
        return 1                                   ;
      }                                            ;
    break                                          ;
  }                                                ;
  //////////////////////////////////////////////////
  QDir root = QDir::current ( )                    ;
  switch ( ioa )                                   {
    case 1                                         :
      ListTarBall ( tfile )                        ;
    return 0                                       ;
    case 2                                         :
      if ( rootdir . length ( ) > 0 )              {
        root = root . absoluteFilePath ( rootdir ) ;
        root = QDir ( rootdir )                    ;
      }                                            ;
      ExtractTarBall ( tfile , root )              ;
    return 0                                       ;
    case 3                                         :
      if ( rootdir . length ( ) > 0 )              {
        root = root . absoluteFilePath ( rootdir ) ;
        root = QDir ( rootdir )                    ;
      }                                            ;
      MakeTarBall    ( tfile , root )              ;
    return 0                                       ;
  }                                                ;
  //////////////////////////////////////////////////
  Help ( )                                         ;
  return 1                                         ;
}

int main(int argc,char ** argv)
{
  QStringList      args = ToArgs ( argc , argv ) ;
  QCoreApplication core          ( argc , argv ) ;
  return Interpret               ( args        ) ;
}
