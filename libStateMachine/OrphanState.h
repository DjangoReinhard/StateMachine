#ifndef ORPHANSTATE_H
#define ORPHANSTATE_H
#include <State.h>


class OrphanState : public State
{
public:
  explicit OrphanState(const QString& name, State* parentState = nullptr, QObject *parent = nullptr);
  virtual ~OrphanState();

  virtual StateTransition* handleEvent(const StateRequestEvent &e) override;
  };
#endif // ORPHANSTATE_H
