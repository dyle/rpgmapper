/****************************************************************************
 *
 * Copyright (C) 2015 Neutrino International Inc.
 *
 * Author   : Brian Lin ( Vladimir Lin , Vladimir Forest )
 * E-mail   : lin.foxman@gmail.com
 *          : lin.vladimir@gmail.com
 *          : wolfram_lin@yahoo.com
 *          : wolfram_lin@sina.com
 *          : wolfram_lin@163.com
 * Skype    : wolfram_lin
 * WeChat   : 153-0271-7160
 * WhatsApp : 153-0271-7160
 * QQ       : lin.vladimir@gmail.com
 * URL      : http://qtlzo.sourceforge.net/
 *
 * QtTAR acts as an interface between Qt and GNU TAR library.
 * Please keep QtTAR as simple as possible.
 *
 * Copyright 2001 ~ 2015
 *
 ****************************************************************************/

 #if defined(__GNUC__) || defined(__GNUCPP__)
 #   define UNUSED   __attribute__((unused))
 #else
 #   define UNUSED
 #endif


#define ENABLE_HIDDEN_FILE_INFO_STRUCTURE
#include <QtTAR/QtTAR>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

QT_BEGIN_NAMESPACE

#ifdef Q_OS_WIN
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup ;
#endif

QtTarBall:: QtTarBall (void)
          : QtTAR     (    )
{
}

QtTarBall::~QtTarBall (void)
{
}

bool QtTarBall::Interval(void)
{
  return true ;
}

void QtTarBall::Report(UNUSED void * hiddenFileInfo)
{
}

void * QtTarBall::NewHiddenFile(void)
{
  HiddenFileInfo * hfi = new HiddenFileInfo ( ) ;
  return (void *)  hfi                          ;
}

void QtTarBall::CleanHiddenFile(void * hiddenFileInfo)
{
  HiddenFileInfo * hfi = (HiddenFileInfo *) hiddenFileInfo ;
  delete hfi                                               ;
}

bool QtTarBall::Write(QIODevice & IO,QByteArray & data)
{
  qint64 w = IO . write ( data )  ;
  return ( data . size ( ) == w ) ;
}

bool QtTarBall::WriteClose(UNUSED QIODevice & IO)
{
  return true ;
}

bool QtTarBall::Read(QIODevice & IO,QByteArray & data,qint64 s)
{
  data = IO . read ( s )          ;
  return ( data . size ( ) == s ) ;
}

bool QtTarBall::Skip(QIODevice & IO,qint64 s)
{
  return IO . seek ( IO . pos ( ) + s ) ;
}

bool QtTarBall::ListFile(UNUSED QDir root,QIODevice & IO,void * hiddenFileInfo)
{
  HiddenFileInfo * hfi = (HiddenFileInfo *) hiddenFileInfo                   ;
  qint64           fs                                                        ;
  Report ( hiddenFileInfo )                                                  ;
  switch ( hfi -> Type )                                                     {
    case Regular                                                             :
      fs = FileBlocks ( hfi -> size       )                                  ;
      if ( ( fs > 0 ) && ( ! Skip ( IO , fs ) ) ) return false               ;
    break                                                                    ;
    case Link                                                                :
    break                                                                    ;
    case Symbol                                                              :
    break                                                                    ;
    case Char                                                                :
    break                                                                    ;
    case Block                                                               :
    break                                                                    ;
    case Directory                                                           :
    break                                                                    ;
    case FIFO                                                                :
    break                                                                    ;
    case Next                                                                :
    break                                                                    ;
    case Extended                                                            :
    break                                                                    ;
    default                                                                  :
    return false                                                             ;
  }                                                                          ;
  return true                                                                ;
}

bool QtTarBall::ExtractFile(QDir root,QIODevice & IO,void * hiddenFileInfo)
{
  HiddenFileInfo * hfi  = (HiddenFileInfo *) hiddenFileInfo                  ;
  QString          path = root . absoluteFilePath ( hfi -> Filename )        ;
  QFileInfo        finf ( path )                                             ;
  QString          fdir = finf . absolutePath ( )                            ;
  root . mkpath ( fdir )                                                     ;
  QFileInfo        DER ( fdir )                                              ;
  if ( ! DER . exists ( ) ) return false                                     ;
  ////////////////////////////////////////////////////////////////////////////
  qint64           written = 0                                               ;
  QFile            F ( path )                                                ;
  if ( ! F . open ( QIODevice::WriteOnly ) ) return false                    ;
  int        bs = BlockSize ( )                                              ;
  QByteArray B                                                               ;
  do                                                                         {
    if ( Read ( IO , B , bs ) )                                              {
      qint64 w = hfi -> size - written                                       ;
      if ( w >= bs )                                                         {
        w = F . write ( B )                                                  ;
        if ( w != bs ) return false                                          ;
        written += bs                                                        ;
        if ( written == hfi -> size ) B . clear ( )                          ;
      } else                                                                 {
        B . resize ( w )                                                     ;
        w = F . write ( B )                                                  ;
        if ( w != B . size ( ) ) return false                                ;
        written += bs                                                        ;
        if ( written == hfi -> size ) B . clear ( )                          ;
      }                                                                      ;
    } else B . clear ( )                                                     ;
  } while ( bs == B . size ( ) )                                             ;
  F . close ( )                                                              ;
  ////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}

bool QtTarBall::ExtractDir(QDir root,UNUSED QIODevice & IO,UNUSED void * hiddenFileInfo)
{
  HiddenFileInfo * hfi  = (HiddenFileInfo *) hiddenFileInfo           ;
  QString          path = root . absoluteFilePath ( hfi -> Filename ) ;
  root . mkpath ( path )                                              ;
  QFileInfo        DER ( path )                                       ;
  return DER . exists  (      )                                       ;
}

bool QtTarBall::ExtractLink(UNUSED QDir root,UNUSED QIODevice & IO,UNUSED void * hiddenFileInfo)
{
  #ifdef Q_OS_WIN
  #else
  #endif
  return true ;
}

bool QtTarBall::ExtractDEVs(UNUSED QDir root,UNUSED QIODevice & IO,UNUSED void * hiddenFileInfo)
{
  #ifdef Q_OS_WIN
  #else
  #endif
  return true ;
}

bool QtTarBall::ExtractNext(UNUSED QDir root,UNUSED QIODevice & IO,UNUSED void * hiddenFileInfo)
{
  return true ;
}

bool QtTarBall::ExtractEXT(UNUSED QDir root,UNUSED QIODevice & IO,UNUSED void * hiddenFileInfo)
{
  return true ;
}

bool QtTarBall::setFileTime(QDir root,UNUSED QIODevice & IO,void * hiddenFileInfo)
{
  HiddenFileInfo * hfi  = (HiddenFileInfo *) hiddenFileInfo                  ;
  QString          path = root . absoluteFilePath ( hfi -> Filename )        ;
  #if defined(Q_OS_WIN)
  HANDLE     hFile                                                           ;
  SYSTEMTIME SCT                                                             ;
  SYSTEMTIME SMT                                                             ;
  FILETIME   FCT                                                             ;
  FILETIME   FMT                                                             ;
  hFile = ::CreateFileW                                                      (
            (LPCWSTR) path . utf16 ( )                                       ,
            GENERIC_READ      | GENERIC_WRITE                                ,
            FILE_SHARE_DELETE | FILE_SHARE_READ                              ,
            NULL                                                             ,
            OPEN_EXISTING                                                    ,
            FILE_FLAG_BACKUP_SEMANTICS                                       ,
            NULL                                                           ) ;
  if ( INVALID_HANDLE_VALUE == hFile ) return false                          ;
  ////////////////////////////////////////////////////////////////////////////
  SCT . wYear         = hfi -> Time    . date ( ) . year      ( )            ;
  SCT . wMonth        = hfi -> Time    . date ( ) . month     ( )            ;
  SCT . wDayOfWeek    = hfi -> Time    . date ( ) . dayOfWeek ( )            ;
  SCT . wDay          = hfi -> Time    . date ( ) . day       ( )            ;
  SCT . wHour         = hfi -> Time    . time ( ) . hour      ( )            ;
  SCT . wMinute       = hfi -> Time    . time ( ) . minute    ( )            ;
  SCT . wSecond       = hfi -> Time    . time ( ) . second    ( )            ;
  SCT . wMilliseconds = hfi -> Time    . time ( ) . msec      ( )            ;
  if ( 7 == SCT . wDayOfWeek ) SCT . wDayOfWeek = 0                          ;
  ////////////////////////////////////////////////////////////////////////////
  SMT . wYear         = hfi -> Lastest . date ( ) . year      ( )            ;
  SMT . wMonth        = hfi -> Lastest . date ( ) . month     ( )            ;
  SMT . wDayOfWeek    = hfi -> Lastest . date ( ) . dayOfWeek ( )            ;
  SMT . wDay          = hfi -> Lastest . date ( ) . day       ( )            ;
  SMT . wHour         = hfi -> Lastest . time ( ) . hour      ( )            ;
  SMT . wMinute       = hfi -> Lastest . time ( ) . minute    ( )            ;
  SMT . wSecond       = hfi -> Lastest . time ( ) . second    ( )            ;
  SMT . wMilliseconds = hfi -> Lastest . time ( ) . msec      ( )            ;
  if ( 7 == SMT . wDayOfWeek ) SCT . wDayOfWeek = 0                          ;
  ////////////////////////////////////////////////////////////////////////////
  ::SystemTimeToFileTime ( &SCT , & FCT                                    ) ;
  ::SystemTimeToFileTime ( &SMT , & FMT                                    ) ;
  ::SetFileTime          ( hFile , &FCT , (LPFILETIME) NULL , &FMT         ) ;
  ::CloseHandle          ( hFile                                           ) ;
  ////////////////////////////////////////////////////////////////////////////
  #endif
  #if defined(Q_OS_IOS) || defined(Q_OS_MACX) || defined(Q_OS_LINUX)
  #endif
  return true                                                                ;
}

bool QtTarBall::setFileMode(UNUSED QDir root,UNUSED QIODevice & IO,UNUSED void * hiddenFileInfo)
{
  return true ;
}

bool QtTarBall::Extract(QDir root,QIODevice & IO,void * hiddenFileInfo)
{
  HiddenFileInfo * hfi = (HiddenFileInfo *) hiddenFileInfo                   ;
  Report ( hiddenFileInfo )                                                  ;
  switch ( hfi -> Type )                                                     {
    case Regular                                                             :
      if ( ! ExtractFile ( root , IO , hiddenFileInfo ) ) return false       ;
      setFileTime ( root , IO , hiddenFileInfo )                             ;
      setFileMode ( root , IO , hiddenFileInfo )                             ;
    break                                                                    ;
    case Link                                                                :
      if ( ! ExtractLink ( root , IO , hiddenFileInfo ) ) return false       ;
      setFileTime ( root , IO , hiddenFileInfo )                             ;
      setFileMode ( root , IO , hiddenFileInfo )                             ;
    break                                                                    ;
    case Symbol                                                              :
    case Char                                                                :
    case Block                                                               :
    case FIFO                                                                :
      if ( ! ExtractDEVs ( root , IO , hiddenFileInfo ) ) return false       ;
      setFileTime ( root , IO , hiddenFileInfo )                             ;
      setFileMode ( root , IO , hiddenFileInfo )                             ;
    break                                                                    ;
    case Directory                                                           :
      if ( ! ExtractDir  ( root , IO , hiddenFileInfo ) ) return false       ;
      setFileTime ( root , IO , hiddenFileInfo )                             ;
      setFileMode ( root , IO , hiddenFileInfo )                             ;
    break                                                                    ;
    case Next                                                                :
      if ( ! ExtractNext ( root , IO , hiddenFileInfo ) ) return false       ;
      setFileTime ( root , IO , hiddenFileInfo )                             ;
      setFileMode ( root , IO , hiddenFileInfo )                             ;
    break                                                                    ;
    case Extended                                                            :
      if ( ! ExtractEXT  ( root , IO , hiddenFileInfo ) ) return false       ;
      setFileTime ( root , IO , hiddenFileInfo )                             ;
      setFileMode ( root , IO , hiddenFileInfo )                             ;
    break                                                                    ;
    default                                                                  :
    return false                                                             ;
  }                                                                          ;
  return true                                                                ;
}

bool QtTarBall::List(QDir root,QString filename)
{
  QFile F ( filename )                               ;
  bool  f = false                                    ;
  if ( ! F . open ( QIODevice::ReadOnly ) ) return f ;
  f = List ( root , F )                              ;
  F . close ( )                                      ;
  return f                                           ;
}

bool QtTarBall::List(QDir root,QIODevice & IO)
{
  bool       f    = true                           ;
  int        bs   = BlockSize ( )                  ;
  bool       drop = false                          ;
  qint64     pos  = 0                              ;
  QByteArray B                                     ;
  while ( ! drop )                                 {
    if ( Read ( IO , B , bs ) )                    {
      pos += bs                                    ;
      if ( isBlock ( B ) )                         {
        HiddenFileInfo * HFI                       ;
        HFI = (HiddenFileInfo *) NewHiddenFile ( ) ;
        if ( QtTAR::Extract ( B , HFI ) )          {
          drop = ! ListFile ( root , IO , HFI )    ;
        } else drop = true                         ;
        CleanHiddenFile ( HFI )                    ;
      } else
      if ( ! isPadding ( B ) ) drop = true         ;
    } else drop = true                             ;
    if ( ! drop ) drop = ! Interval ( )            ;
  }                                                ;
  return f                                         ;
}

bool QtTarBall::Extract(QDir root,QString filename)
{
  QFile F ( filename )                               ;
  bool  f = false                                    ;
  if ( ! F . open ( QIODevice::ReadOnly ) ) return f ;
  f = Extract ( root , F )                           ;
  F . close ( )                                      ;
  return f                                           ;
}

bool QtTarBall::Extract(QDir root,QIODevice & IO)
{
  bool       f    = true                           ;
  int        bs   = BlockSize ( )                  ;
  bool       drop = false                          ;
  qint64     pos  = 0                              ;
  QByteArray B                                     ;
  QList<HiddenFileInfo *> HFIs                     ;
  while ( ! drop )                                 {
    if ( Read ( IO , B , bs ) )                    {
      pos += bs                                    ;
      if ( isBlock ( B ) )                         {
        HiddenFileInfo * HFI                       ;
        HFI = (HiddenFileInfo *) NewHiddenFile ( ) ;
        if ( QtTAR::Extract ( B , HFI ) )          {
          drop = ! Extract ( root , IO , HFI )     ;
        } else drop = true                         ;
        if ( Directory == HFI -> Type )            {
          HFIs << HFI                              ;
        } else CleanHiddenFile ( HFI )             ;
      } else
      if ( ! isPadding ( B ) ) drop = true         ;
    } else drop = true                             ;
    if ( ! drop ) drop = ! Interval ( )            ;
  }                                                ;
  //////////////////////////////////////////////////
  if ( HFIs . count ( ) > 0 )                      {
    for (int i = 0 ; i < HFIs . count ( ) ; i++ )  {
      setFileTime     ( root , IO , HFIs [ i ]   ) ;
      CleanHiddenFile (             HFIs [ i ]   ) ;
    }                                              ;
  }                                                ;
  //////////////////////////////////////////////////
  return f                                         ;
}

QFileInfoList QtTarBall::Listing(UNUSED QDir & root,QDir source)
{
  return source . entryInfoList ( QDir::NoDotAndDotDot | QDir::AllEntries ) ;
}

bool QtTarBall::ToHiddenFileInfo(QDir & root,QFileInfo & file,void * hiddenFileInfo)
{
  HiddenFileInfo   * hfi = (HiddenFileInfo *) hiddenFileInfo                 ;
  QFile::Permissions mode                                                    ;
  hfi -> Archive  = true                                                     ;
  hfi -> uid      = file . ownerId       ( )                                 ;
  hfi -> uname    = file . owner         ( )                                 ;
  hfi -> gid      = file . groupId       ( )                                 ;
  hfi -> gname    = file . group         ( )                                 ;
  hfi -> LinkName = file . symLinkTarget ( )                                 ;
  hfi -> Time     = file . created       ( )                                 ;
  hfi -> Lastest  = file . lastModified  ( )                                 ;
  hfi -> Prefix   = ""                                                       ;
  hfi -> CheckSum = "       "                                                ;
  hfi -> Comment  = ""                                                       ;
  ////////////////////////////////////////////////////////////////////////////
  hfi -> Root     = root . absolutePath     ( )                              ;
  hfi -> Filename = file . absoluteFilePath ( )                              ;
  if ( hfi -> Filename . length ( ) >= hfi -> Root . length ( ) )            {
    QString L = hfi -> Filename . left ( hfi -> Root . length ( ) )          ;
    if ( L == hfi -> Root )                                                  {
      hfi -> Filename . remove ( 0 , hfi -> Root . length ( ) )              ;
    }                                                                        ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  hfi -> size     = 0                                                        ;
  if ( file . isFile ( ) ) hfi -> size = file . size ( )                     ;
  ////////////////////////////////////////////////////////////////////////////
  #ifdef Q_OS_WIN
  qt_ntfs_permission_lookup++                                                ;
  mode = file . permissions ( )                                              ;
  qt_ntfs_permission_lookup--                                                ;
  hfi -> mode     = (qint64) mode                                            ;
  #else
  #endif
  ////////////////////////////////////////////////////////////////////////////
  hfi -> System   = ""                                                       ;
  #ifdef Q_OS_WIN
  hfi -> System   = "Windows"                                                ;
  #endif
  #ifdef Q_OS_MACX
  hfi -> System   = "MacOSX"                                                 ;
  #endif
  #ifdef Q_OS_LINUX
  hfi -> System   = "Linux"                                                  ;
  #endif
  #ifdef Q_OS_ANDROID
  hfi -> System   = "Android"                                                ;
  #endif
  #ifdef Q_OS_IOS
  hfi -> System   = "iPhoneOS"                                               ;
  #endif
  ////////////////////////////////////////////////////////////////////////////
  #ifdef Q_OS_WIN
  hfi -> Major    = 0                                                        ;
  hfi -> Minor    = 0                                                        ;
  #else
  #endif
  ////////////////////////////////////////////////////////////////////////////
  if ( file . isFile    ( ) )                                                {
    hfi -> Type = Regular                                                    ;
  } else
  if ( file . isDir     ( ) )                                                {
    hfi -> Type = Directory                                                  ;
  } else
  if ( file . isSymLink ( ) )                                                {
    hfi -> Type = Link                                                       ;
  } else                                                                     {
    #ifdef Q_OS_WIN
    #else
    #endif
  }                                                                          ;
  return true                                                                ;
}

bool QtTarBall::WriteFile(QIODevice & IO,QFileInfo & file)
{
  QFile F ( file . absoluteFilePath ( ) )                       ;
  if ( ! F . open ( QIODevice::ReadOnly )        ) return false ;
  QByteArray H                                                  ;
  int        bs = BlockSize ( )                                 ;
  do                                                            {
    H = F . read ( bs )                                         ;
    if ( H . size ( ) == bs )                                   {
      if ( ! Write ( IO , H ) ) return false                    ;
    } else
    if ( ( H . size ( ) > 0 ) && ( H . size ( ) < bs ) )        {
      QByteArray B = H                                          ;
      QByteArray E ( bs - H . size ( ) , 0 )                    ;
      B . append ( E )                                          ;
      if ( ! Write ( IO , B ) ) return false                    ;
    }                                                           ;
  } while ( H . size ( ) == bs )                                ;
  F . close ( )                                                 ;
  return true                                                   ;
}

bool QtTarBall::WriteTAR(QIODevice & IO,QDir & root,QFileInfo & file)
{
  HiddenFileInfo * HFI                            ;
  HFI = (HiddenFileInfo *) NewHiddenFile ( )      ;
  if ( ! ToHiddenFileInfo ( root , file , HFI ) ) {
    CleanHiddenFile ( HFI )                       ;
    return false                                  ;
  }                                               ;
  QByteArray H                                    ;
  int        bs = BlockSize ( )                   ;
  if ( ! Bale ( HFI , H ) )                       {
    CleanHiddenFile ( HFI )                       ;
    return false                                  ;
  }                                               ;
  CleanHiddenFile ( HFI )                         ;
  if ( H . size ( ) != bs          ) return false ;
  if ( ! Write ( IO , H )          ) return false ;
  if ( ! file . isFile ( )         ) return true  ;
  return WriteFile ( IO , file )                  ;
}

bool QtTarBall::TarBall(QString filename,QDir root,QDir source,bool recursive)
{
  QFile F ( filename )                                ;
  bool  f = false                                     ;
  if ( ! F . open ( QIODevice::WriteOnly ) ) return f ;
  f = TarBall ( F, root , source , recursive )        ;
  WriteClose  ( F                            )        ;
  F . close   (                              )        ;
  return f                                            ;
}

bool QtTarBall::TarBall(QIODevice & IO,QDir root,QDir source,bool recursive)
{
  QFileInfoList F = Listing ( root , source )                            ;
  if ( F . count ( ) <= 0 ) return false                                 ;
  for (int i = 0 ; i < F . count ( ) ; i++ )                             {
    if ( ! WriteTAR ( IO , root , F [ i ] ) ) return false               ;
    if ( ! Interval ( )                     ) return false               ;
  }                                                                      ;
  if ( ! recursive ) return true                                         ;
  for (int i = 0 ; i < F . count ( ) ; i++ )                             {
    if ( F [ i ] . isDir ( ) )                                           {
      TarBall ( IO , root , F [ i ] . absoluteFilePath ( ) , recursive ) ;
      if ( ! Interval ( )                   ) return false               ;
    }                                                                    ;
  }                                                                      ;
  return true                                                            ;
}

QT_END_NAMESPACE
