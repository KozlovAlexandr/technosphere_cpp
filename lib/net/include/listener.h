#pragma once
#include "buffered_connection.h"

namespace net
{

class IServiceListener
{
public:
    virtual ~IServiceListener() = default;;
    virtual void onNewConnection(BufferedConnection& cn) = 0;
    virtual void onClose(BufferedConnection& cn)         = 0;
    virtual void onWriteDone(BufferedConnection& cn)     = 0;
    virtual void onReadAvailable(BufferedConnection& cn) = 0;
    virtual void onError(BufferedConnection& cn)         = 0;
};

}  // namespace net