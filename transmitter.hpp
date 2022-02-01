#ifndef TRANSMITTER_HPP
#define TRANSMITTER_HPP

#include "wave_reader.hpp"
#include <mutex>

class ClockOutput;

class Transmitter
{
    public:
        Transmitter();
        virtual ~Transmitter();
        Transmitter(const Transmitter &) = delete;
        Transmitter(Transmitter &&) = delete;
        Transmitter &operator=(const Transmitter &) = delete;
        void Transmit(WaveReader &reader, float frequency, float bandwidth, unsigned dmaChannel, bool preserveCarrier);
        void Stop();
    private:
        void TransmitViaCpu(WaveReader &reader, ClockOutput &output, unsigned sampleRate, unsigned bufferSize, unsigned clockDivisor, unsigned divisorRange);
        void TransmitViaDma(WaveReader &reader, ClockOutput &output, unsigned sampleRate, unsigned bufferSize, unsigned clockDivisor, unsigned divisorRange, unsigned dmaChannel);
        static void TransmitterThread(Transmitter *instance, ClockOutput *output, unsigned sampleRate, unsigned clockDivisor, unsigned divisorRange, unsigned *sampleOffset, std::vector<Sample> *samples);

        static bool transmitting;
        ClockOutput *output;
        std::mutex access;
        bool stopped;
};

#endif // TRANSMITTER_HPP
