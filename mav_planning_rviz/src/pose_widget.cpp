#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>
#include <QTableView>
#include <QTableWidget>

#include "mav_planning_rviz/pose_widget.h"

namespace mav_planning_rviz {

PoseWidget::PoseWidget(QWidget* parent) : QWidget(parent) { createTable(); }

void PoseWidget::createTable() {
  table_widget_ = new QTableWidget(this);
  table_widget_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  table_widget_->setRowCount(1);
  table_widget_->setColumnCount(4);
  table_headers_ << "x [m]"
                 << "y [m]"
                 << "z [m]" << QString::fromUtf8("yaw [°]");
  table_widget_->setHorizontalHeaderLabels(table_headers_);
  table_widget_->verticalHeader()->setVisible(false);
  // table_widget_->setEditTriggers(QAbstractItemView::NoEditTriggers);
  // table_widget_->setSelectionBehavior(QAbstractItemView::SelectRows);
  // table_widget_->setSelectionMode(QAbstractItemView::SingleSelection);
  table_widget_->setShowGrid(true);
  // table_widget_->setMinimumHeight(10);
  // table_widget_->setMinimumWidth(10);
  table_widget_->setItemDelegate(new DoubleTableDelegate);

  table_widget_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  table_widget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  table_widget_->resizeColumnsToContents();
  table_widget_->setFixedSize(table_widget_->horizontalHeader()->length(),
                              table_widget_->verticalHeader()->length() +
                                  table_widget_->horizontalHeader()->height());

  for (int i = 0; i < 4; i++) {
    table_widget_->setItem(0, i, new QTableWidgetItem("0.0"));
  }

  // table_widget_->setStyleSheet("QTableView {selection-background-color:
  // red;}");
  // table_widget_->setGeometry(QApplication::desktop()->screenGeometry());
  /* for (int i = 0; i < table_widget_->columnCount(); ++i) {
    table_widget_->resizeColumnToContents(i);
  }
  table_widget_->resizeRowToContents(0); */
}

void PoseWidget::getPose(mav_msgs::EigenTrajectoryPoint* point) const {
  point->position_W.x() = table_widget_->item(0, 0)->text().toDouble();
  point->position_W.y() = table_widget_->item(0, 1)->text().toDouble();
  point->position_W.z() = table_widget_->item(0, 2)->text().toDouble();
  point->setFromYaw(table_widget_->item(0, 0)->text().toDouble());
}

/*
// From
//
https://stackoverflow.com/questions/8766633/how-to-determine-the-correct-size-of-a-qtablewidget
QSize PoseWidget::getTableSize(QTableWidget* t) const {
 int w = t->verticalHeader()->width() + 4;  // +4 seems to be needed
 for (int i = 0; i < t->columnCount(); i++)
   w += t->columnWidth(i);  // seems to include gridline (on my machine)
 int h = t->horizontalHeader()->height() + 4;
 for (int i = 0; i < t->rowCount(); i++) h += t->rowHeight(i);
 return QSize(w, h);
}
*/

}  // namespace mav_planning_rviz
