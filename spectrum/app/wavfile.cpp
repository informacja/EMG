/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qendian.h>
#include <QVector>
#include <QDebug>
//#include "utils.h"
#include "wavfile.h"

struct chunk
{
    char        id[4];
    quint32     size;
};

struct RIFFHeader
{
    chunk       descriptor;     // "RIFF"
    char        type[4];        // "WAVE"
};

struct WAVEHeader
{
    chunk       descriptor;
    quint16     audioFormat;
    quint16     numChannels;
    quint32     sampleRate;
    quint32     byteRate;
    quint16     blockAlign;
    quint16     bitsPerSample;
};

struct DATAHeader
{
    chunk       descriptor;
};

struct CombinedHeader
{
    RIFFHeader  riff;
    WAVEHeader  wave;
};

WavFile::WavFile(QObject *parent)
    : QFile(parent)
    , m_headerLength(0)
{

}

bool WavFile::open(const QString &fileName)
{
    close();
    setFileName(fileName);
    return QFile::open(QIODevice::ReadOnly) && readHeader();
}

const QAudioFormat &WavFile::fileFormat() const
{
    return m_fileFormat;
}

qint64 WavFile::headerLength() const
{
return m_headerLength;
}

bool WavFile::readHeader()
{
    seek(0);
    CombinedHeader header;
    bool result = read(reinterpret_cast<char *>(&header), sizeof(CombinedHeader)) == sizeof(CombinedHeader);
    if (result) {
        if ((memcmp(&header.riff.descriptor.id, "RIFF", 4) == 0
            || memcmp(&header.riff.descriptor.id, "RIFX", 4) == 0)
            && memcmp(&header.riff.type, "WAVE", 4) == 0
            && memcmp(&header.wave.descriptor.id, "fmt ", 4) == 0
            && (header.wave.audioFormat == 1 || header.wave.audioFormat == 0)) {

            // Read off remaining header information
            DATAHeader dataHeader;

            if (qFromLittleEndian<quint32>(header.wave.descriptor.size) > sizeof(WAVEHeader)) {
                // Extended data available
                quint16 extraFormatBytes;
                if (peek((char*)&extraFormatBytes, sizeof(quint16)) != sizeof(quint16))
                    return false;
                const qint64 throwAwayBytes = sizeof(quint16) + qFromLittleEndian<quint16>(extraFormatBytes);
                if (read(throwAwayBytes).size() != throwAwayBytes)
                    return false;
            }

            if (read((char*)&dataHeader, sizeof(DATAHeader)) != sizeof(DATAHeader))
                return false;

            // Establish format
            if (memcmp(&header.riff.descriptor.id, "RIFF", 4) == 0)
                m_fileFormat.setByteOrder(QAudioFormat::LittleEndian);
            else
                m_fileFormat.setByteOrder(QAudioFormat::BigEndian);

            int bps = qFromLittleEndian<quint16>(header.wave.bitsPerSample);
            m_fileFormat.setChannelCount(qFromLittleEndian<quint16>(header.wave.numChannels));
            m_fileFormat.setCodec("audio/pcm");
            m_fileFormat.setSampleRate(qFromLittleEndian<quint32>(header.wave.sampleRate));
            m_fileFormat.setSampleSize(qFromLittleEndian<quint16>(header.wave.bitsPerSample));
            m_fileFormat.setSampleType(bps == 8 ? QAudioFormat::UnSignedInt : QAudioFormat::SignedInt);
        } else {
            result = false;
        }
    }
    m_headerLength = pos();
    return result;
}

class WavPcmFile : public QFile {
public:
WavPcmFile(const QString & name, const QAudioFormat & format, QObject *parent = 0);
bool open();
void close();

private:
void writeHeader();
bool hasSupportedFormat();
QAudioFormat format;
};


//WavPcmFile::WavPcmFile(const QString & name, const QAudioFormat & format_, QObject *parent_)
//: QFile(name, parent_), format(format_)
//{
//}

//bool WavPcmFile::hasSupportedFormat()
//{
//return (format.sampleSize() == 8
//&& format.sampleType() == QAudioFormat::UnSignedInt)
//|| (format.sampleSize() > 8
//&& format.sampleType() == QAudioFormat::SignedInt
//&& format.byteOrder() == QAudioFormat::LittleEndian);
//}

//bool WavPcmFile::open()
//{
//if (!hasSupportedFormat()) {
//setErrorString("Wav PCM supports only 8-bit unsigned samples "
//"or 16-bit (or more) signed samples (in little endian)");
//return false;
//} else {
//if (!QFile::open(ReadWrite | Truncate))
//return false;
//writeHeader();
//return true;
//}
//}

//void WavPcmFile::writeHeader()
//{
//QDataStream out(this);
//out.setByteOrder(QDataStream::LittleEndian);

//// RIFF chunk
//out.writeRawData("RIFF", 4);
//out << quint32(0); // Placeholder for the RIFF chunk size (filled by close())
//out.writeRawData("WAVE", 4);

//// Format description chunk
//out.writeRawData("fmt ", 4);
//out << quint32(16); // "fmt " chunk size (always 16 for PCM)
//out << quint16(1); // data format (1 => PCM)
//out << quint16(format.channelCount());
//out << quint32(format.sampleRate());
//out << quint32(format.sampleRate() * format.channelCount()
//* format.sampleSize() / 8 ); // bytes per second
//out << quint16(format.channelCount() * format.sampleSize() / 8); // Block align
//out << quint16(format.sampleSize()); // Significant Bits Per Sample

//// Data chunk
//out.writeRawData("data", 4);
//out << quint32(0); // Placeholder for the data chunk size (filled by close())

//Q_ASSERT(pos() == 44); // Must be 44 for WAV PCM
//}

//void WavPcmFile::close()
//{
//// Fill the header size placeholders
//quint32 fileSize = size();

//QDataStream out(this);
//// Set the same ByteOrder like in writeHeader()
//out.setByteOrder(QDataStream::LittleEndian);
//// RIFF chunk size
//seek(4);
//out << quint32(fileSize - 8);

//// data chunk size
//seek(40);
//out << quint32(fileSize - 44);

//QFile::close();
//}
// Starts the recording
//WavPcmFile *m_file = new WavPcmFile("Filename.wav", m_audioInput->format(), this);
//if(m_file.open()) {
//m_audioInput->start(m_file);
//} else {
//// Error
//}

//// Stops the recording
////m_audioInput->stop();
////m_file->close();



//AudioOutput::createAudioOutput(AudioBuffer * audioBuffer)
//{
//m_audioBuffer = audioBuffer;//new AudioBuffer(m_settings,this);
//m_audioOutput = new QAudioOutput(m_settings,this);

//QString fileName = QString("C:/AudiofromStation(%1,%2,%3).wav")
//.arg(m_audioOutput->format().frequency())
//.arg(m_audioOutput->format().channelCount())
//.arg(m_audioOutput->format().sampleSize());

//m_File = new QFile(fileName);
//m_File->open(QIODevice::WriteOnly);
//m_File->write(QByteArray(44, '\x55'));

//connect(m_audioOutput,SIGNAL(notify()),SLOT(status()));
//connect(m_audioOutput,SIGNAL(stateChanged(QAudio::State)),SLOT(state(QAudio::State)));
//}

//AudioOutput::stop()
//{
//m_audioOutput->stop();
//m_File->seek(0);
//writeWavHeader(m_File);
//m_File->close();
//// m_audioBuffer->clear();
//// m_audioBuffer->stop();
//m_output = NULL;
//}
