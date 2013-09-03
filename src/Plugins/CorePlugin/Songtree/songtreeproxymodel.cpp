#include "songtreeproxymodel.h"
#include "songtreeitem.h"

#include <QFont>
#include <QDebug>
#include <QStack>
#include <QApplication>
#include <QPalette>

using namespace Core;
SongtreeProxyModel::SongtreeProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    textColor = qApp->palette().color(QPalette::HighlightedText);

    QColor tmp = qApp->palette().color(QPalette::Text);
    disabledTextColor = QColor(tmp.red(), tmp.green(), tmp.blue(), 70);
    this->setFilterCaseSensitivity(Qt::CaseInsensitive);
}


bool SongtreeProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    SongTreeItem* item = (SongTreeItem*) index.internalPointer();
    bool result = (item->ancestorsContains(filterRegExp())||item->subTreeContains(filterRegExp()));
    return result;
}


QVariant SongtreeProxyModel::data( const QModelIndex & index, int role ) const
{
  QModelIndex sourceIndex = mapToSource(index);
  QString name = sourceIndex.data().toString();
  bool highlight = name.contains(filterRegExp());

  if (!filterRegExp().isEmpty())
  {
      if (role == Qt::ForegroundRole)
      {
          if (highlight)
          {
              return QVariant(textColor);
          }
          else
          {
            return QVariant(disabledTextColor);
          }
      }

      if (role == Qt::FontRole && highlight)
      {
          QFont font =  sourceIndex.data(Qt::FontRole).value<QFont>();
          font.setBold(true);
          //font.setItalic(true);
          return font;
      }
  }
  return sourceIndex.data(role);
}

void SongtreeProxyModel::expandIndex(QModelIndex index)
{
    Q_EMIT expandIndex(mapFromSource(index));
}
