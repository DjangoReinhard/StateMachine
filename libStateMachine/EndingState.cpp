#include <EndingState.h>


EndingState::EndingState(const QString& name, State* parentState, QObject *parent)
 : State(name, parentState, parent) {
  }


EndingState::~EndingState() {
  }
