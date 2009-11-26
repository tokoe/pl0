
#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "identifiermanager.h"

typedef struct Transition Transition;

class HandlerBase;

class Parser
{
  public:
    Parser();
    ~Parser();

    void load( QIODevice *device );

    bool parse( QIODevice *output );
    QString errorText() const;

    static void outputGraphs();

  private:
    bool parse( Transition *transition );
    Tokenizer mTokenizer;
    QString mErrorText;
    IdentifierManager mIdentifierManager;
    QList<HandlerBase*> mActionHandlers;
};

#endif
