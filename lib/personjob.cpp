/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include "personjob.h"

#include "personparser.h"

#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QNetworkReply>

//#include <klocale.h>


using namespace Attica;


PersonJob::PersonJob(QNetworkReply* data)
    :AtticaBaseJob(data)
{
}


Person PersonJob::person() const
{
    return m_person;
}


void PersonJob::parse(const QString& xml)
{
    m_person = Person::Parser().parse( xml );

    if (!m_person.avatarUrl().isEmpty()) {
        qDebug() << "Getting avatar from" << m_person.avatarUrl();
        // TODO
        // either create another qnam instance or retrieve the old one from provider (?)
    }
}


/*
void PersonJob::doWork()
{
  qDebug() << m_url;

  m_job = KIO::get( m_url, KIO::NoReload, KIO::HideProgressInfo );
  connect( m_job, SIGNAL( result( KJob * ) ),
    SLOT( slotUserJobResult( KJob * ) ) );
  connect( m_job, SIGNAL( data( KIO::Job *, const QByteArray & ) ),
    SLOT( slotUserJobData( KIO::Job *, const QByteArray & ) ) );
}

void PersonJob::slotUserJobResult( KJob *job )
{
  m_job = 0;

  if ( job->error() ) {
    setError( job->error() );
    setErrorText( job->errorText() );
  
    emitResult();
  } else {
    // qDebug() << m_userData;
    m_person = Person::Parser().parse( m_userData );
  
    if (!m_person.avatarUrl().isEmpty()) {
      qDebug() << "Getting avatar from" << m_person.avatarUrl();

      m_job = KIO::get( m_person.avatarUrl(), KIO::NoReload,
        KIO::HideProgressInfo );
      connect( m_job, SIGNAL( result( KJob * ) ),
        SLOT( slotAvatarJobResult( KJob * ) ) );
      connect( m_job, SIGNAL( data( KIO::Job *, const QByteArray & ) ),
        SLOT( slotAvatarJobData( KIO::Job *, const QByteArray & ) ) );
    } else {
      emitResult();
    }
  }
}

void PersonJob::slotUserJobData( KIO::Job *, const QByteArray &data )
{
  m_userData.append( QString::fromUtf8( data.data(), data.size() + 1 ) );
}

void PersonJob::slotAvatarJobResult( KJob *job )
{
  m_job = 0;

  if ( job->error() ) {
    qWarning() << "Error retrieving Avatar:" << job->errorText();
  } else {
    QPixmap pic;
    if ( pic.loadFromData( m_avatarData ) ) {
      m_person.setAvatar( pic );
    }
  }
  
  emitResult();
}

void PersonJob::slotAvatarJobData( KIO::Job *, const QByteArray &data )
{
  m_avatarData.append( data );
}
*/

#include "personjob.moc"
