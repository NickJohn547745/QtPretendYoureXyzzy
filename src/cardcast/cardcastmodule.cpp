#include "cardcastmodule.h"

void CardcastModule::configure()
{
    struct main : CardcastModule
    {
        QAtomicInt provideCardId()
        {
            return cardId->deref();
        }
    };
}
