#ifndef QDATAPARSER_H
#define QDATAPARSER_H

#include "qccnode.h"
#include "qcccontainerlayer.h"
#include "qcclabelatlas.h"
#include "qcclabelttf.h"
#include "qcclayer.h"
#include "qcclayercolor.h"
#include "qccmenuitemimage.h"
#include "qccprogresstimer.h"
#include "qccscale9sprite.h"
#include "qccscrollview.h"
#include "qccsprite.h"

class QDataParser
{
public:
    virtual ~QDataParser(){}
    virtual QCCNode* readUIFile(QString filePath);
    virtual bool writeUIFile(QString filePath, QCCNode* root);
};

#endif // QDATAPARSER_H
