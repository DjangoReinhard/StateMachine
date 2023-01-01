#ifndef ENDINGSTATE_H
#define ENDINGSTATE_H
#include <State.h>


class EndingState : public State
{
public:
  explicit EndingState(const QString& name, State* parentState = nullptr, QObject *parent = nullptr);
  virtual ~EndingState();
  };
#endif // ENDINGSTATE_H
