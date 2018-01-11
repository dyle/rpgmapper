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

#ifndef QT_TAR_H
#define QT_TAR_H

#include <QtCore>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTTAR_LIB)
#      define Q_TAR_EXPORT Q_DECL_EXPORT
#    else
#      define Q_TAR_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_TAR_EXPORT
#endif

#define QT_TAR_LIB 1

#ifdef ENABLE_HIDDEN_FILE_INFO_STRUCTURE

// This is for internal use only
// User should define your own structure the same with HiddenFileInfo

typedef enum      {
  None      =  0  ,
  Regular   =  1  ,
  Link      =  2  ,
  Symbol    =  3  ,
  Char      =  4  ,
  Block     =  5  ,
  Directory =  6  ,
  FIFO      =  7  ,
  Reserved  =  8  ,
  Next      =  9  ,
  Extended  = 10  }
  HiddenFileTypes ;

typedef struct HiddenFileInfo {
  bool            Archive     ; /* inside a Tar file or Zip file, and so on */
  QString         Root        ; /* Root directory or tarball name */
  QString         Filename    ; /* Filename or directory name of this entry */
  QString         System      ; /* Normally, this is operation system */
  qint64          mode        ; /* Unix only */
  qint64          uid         ; /* Unix only */
  qint64          gid         ; /* Unix only */
  qint64          size        ; /* File size, for directory, it is 0 */
  QDateTime       Time        ; /* Creation time */
  QDateTime       Lastest     ; /* Last modified */
  QString         CheckSum    ; /* CheckSum of this file */
  HiddenFileTypes Type        ; /* File Type */
  QString         LinkName    ; /* Unix only */
  QString         uname       ; /* Unix only */
  QString         gname       ; /* Unix only */
  qint64          Major       ; /* Unix only */
  qint64          Minor       ; /* Unix only */
  QString         Prefix      ; /* Normally, this is prefix directory */
  QString         Comment     ; /* This is from GZIP format, however, sometimes it is useful */
} HiddenFileInfo              ;

#endif

class Q_TAR_EXPORT QtTAR     ;
class Q_TAR_EXPORT QtTarBall ;

class Q_TAR_EXPORT QtTAR
{
  public:

    explicit       QtTAR        (void) ;
    virtual       ~QtTAR        (void) ;

    virtual int    BlockSize    (void) const ;
    virtual bool   isBlock      (QByteArray & block) ;
    virtual bool   isPadding    (QByteArray & block) ;

    virtual qint64 FileBlocks   (qint64 size) ;
    virtual int    Checksum     (QByteArray & block,char replace = ' ') ;

    virtual bool   Extract      (QByteArray & block         ,void       * hiddenFileInfo) ; // block => File
    virtual bool   Bale         (void       * hiddenFileInfo,QByteArray & data          ) ; // File  <= Data

  protected:

    QString        toOct        (int checksum) ;
    void           PackOct      (char * buf,qint64 size,int length) ;
    qint64         FromOct      (char * buf,int length) ;

  private:

    void           Copy         (char * buf,QString string) ;

} ;

class Q_TAR_EXPORT QtTarBall : public QtTAR
{
  public:

    explicit       QtTarBall        (void) ;
    virtual       ~QtTarBall        (void) ;

    virtual bool   List             (QDir root,QIODevice & IO) ;
    virtual bool   List             (QDir root,QString filename) ;

    virtual bool   Extract          (QDir root,QIODevice & IO) ;
    virtual bool   Extract          (QDir root,QString filename) ;

    virtual bool   TarBall          (QIODevice & IO,QDir root,QDir source,bool recursive = true) ;
    virtual bool   TarBall          (QString filename,QDir root,QDir source,bool recursive = true) ;

  protected:

    virtual bool   Interval         (void) ;
    virtual void   Report           (void * hiddenFileInfo) ;

    virtual bool   ListFile         (QDir root,QIODevice & IO,void * hiddenFileInfo) ;
    virtual bool   Extract          (QDir root,QIODevice & IO,void * hiddenFileInfo) ;

    virtual bool   Read             (QIODevice & IO,QByteArray & data,qint64 size) ;
    virtual bool   Skip             (QIODevice & IO,qint64 size) ;
    virtual bool   Write            (QIODevice & IO,QByteArray & data) ;
    virtual bool   WriteClose       (QIODevice & IO) ;
    virtual bool   WriteFile        (QIODevice & IO,QFileInfo & file) ;

    virtual bool   ExtractFile      (QDir root,QIODevice & IO,void * hiddenFileInfo) ;
    virtual bool   ExtractDir       (QDir root,QIODevice & IO,void * hiddenFileInfo) ;
    virtual bool   ExtractLink      (QDir root,QIODevice & IO,void * hiddenFileInfo) ;
    virtual bool   ExtractDEVs      (QDir root,QIODevice & IO,void * hiddenFileInfo) ;
    virtual bool   ExtractNext      (QDir root,QIODevice & IO,void * hiddenFileInfo) ;
    virtual bool   ExtractEXT       (QDir root,QIODevice & IO,void * hiddenFileInfo) ;
    virtual bool   setFileTime      (QDir root,QIODevice & IO,void * hiddenFileInfo) ;
    virtual bool   setFileMode      (QDir root,QIODevice & IO,void * hiddenFileInfo) ;

    virtual QFileInfoList Listing   (QDir & root,QDir source) ;
    virtual bool   WriteTAR         (QIODevice & IO,QDir & root,QFileInfo & file) ;
    virtual bool   ToHiddenFileInfo (QDir & root,QFileInfo & file,void * hiddenFileInfo) ;

    virtual void * NewHiddenFile    (void) ;
    virtual void   CleanHiddenFile  (void * hiddenFileInfo) ;

  private:

} ;

QT_END_NAMESPACE

#endif
