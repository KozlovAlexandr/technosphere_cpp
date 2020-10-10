#ifndef PROCESS_PIPEWRAPPER_H
#define PROCESS_PIPEWRAPPER_H

namespace process
{

class PipeWrapper
{
public:
    PipeWrapper();
    ~PipeWrapper();

    void close();
    void closeIn();
    void closeOut();

    void open();

    [[nodiscard]] int getInFd() const;
    [[nodiscard]] int getOutFd() const;
private:
    int pipeFd_[2];
};

} // namespace process

#endif //PROCESS_PIPEWRAPPER_H
