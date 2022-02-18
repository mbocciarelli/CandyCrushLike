//
// Created by Daniel Chiquet on 17/02/2022.
//

#include "stack"
#include "memory"

#include "State.h"

namespace Engine {
    class StateMan {
    private:
        std::stack<std::unique_ptr<State>> m_stateStack;
        std::unique_ptr<State> m_newState;

        bool m_add;
        bool m_replace;
        bool m_remove;

    public:
        StateMan();
        ~StateMan();

        void add(std::unique_ptr<State> toAdd, bool replace=false);
        void PopCurrent();
        void ProcessStateChange();
        std::unique_ptr<State>& GetCurrent();
    };

}