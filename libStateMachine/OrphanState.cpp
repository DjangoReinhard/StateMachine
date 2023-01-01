#include <OrphanState.h>


OrphanState::OrphanState(const QString& name, State* parentState, QObject *parent)
 : State(name, parentState, parent) {
  }


OrphanState::~OrphanState() {
  }


StateTransition* OrphanState::handleEvent(const StateRequestEvent &e) {
  if (transitions.contains(e.code()))
     return transitions[e.code()];
  return nullptr;
  }
