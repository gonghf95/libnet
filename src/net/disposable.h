#ifndef NETWORK_DISPOSABLE_H
#define NETWORK_DISPOSABLE_H

class IDisposable
{
public:
	virtual ~IDisposable() = default;
	virtual void Dispose() = 0;
};

#endif /* NETWORK_DISPOSABLE_H */
