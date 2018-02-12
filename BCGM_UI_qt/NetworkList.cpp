/**
  \file HpavNetworkList.cpp

  \author Jack.Li
*/

#include "NetworkList.h"
#include "ui_NetworkList.h"

#include "Application.h"
#include "BCGMApp.h"

#include <QItemDelegate>
#include <QPainter>
#include <QStandardItemModel>
#include <QUrl>
#include <QDesktopServices>
#include <QStyledItemDelegate>
#include <QClipboard>
#include <QVBoxLayout>
#include <QtConcurrentRun>

#ifdef WIN32
#define snprintf _snprintf
#endif

using namespace std;

static QStringList m_data;
static int count_;


class NetWorkIplabel : public QItemDelegate
{
public:
	NetWorkIplabel(QWidget * parent = 0)
		: QItemDelegate(parent){
		font_underline_.setPointSizeF(1.1 * font_underline_.pointSizeF());
		font_underline_.setUnderline(true);
		font_.setPointSizeF(1.1 * font_underline_.pointSizeF());
	} 

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		painter->save();
		if (3 == index.column()){ 
			if (m_data.size() <= index.row())
				return;
			QString url = static_cast<QString>(m_data.at(index.row()));
			if(url.compare("unavailable")){
				painter->setPen(QColor(Qt::blue));
				painter->setFont(font_underline_);
			} else
				painter->setFont(font_);
			QStyleOptionViewItem myOption = option;
			myOption.displayAlignment = Qt::AlignHCenter | Qt::AlignVCenter;
			myOption.palette.setColor(QPalette::HighlightedText, 
				index.data(Qt::TextColorRole).value<QColor>());
			QApplication::style()->drawItemText(painter, myOption.rect, 
				myOption.displayAlignment, QApplication::palette(), true, url);
		}
		painter->restore();
	}

	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
	{
		if (event->type() == QEvent::MouseButtonPress) {
			if (m_data.size() <= index.row())
				return false;
			QString url_ = static_cast<QString>(m_data.at(index.row()));
			if (url_.isEmpty() || !url_.compare("unavailable"))
				return true;
			char url[255];
			snprintf(url, sizeof(url), "http://%s/", url_.toStdString().c_str());
			QDesktopServices::openUrl(QUrl(url)); 
		} 
		return true;
	}

	~NetWorkIplabel() {}

private:
	QFont font_underline_;
	QFont font_;
};


struct NetworkList::Private
{
    Private(NetworkList * parent) : p_(parent), iplink_(0)
	{

    }
    ///
    void fillNetworkList();
    ///
    Ui::NetWorkList ui;
    NetworkList * p_;
	///
	QStandardItemModel * network_list_model_;
    NetWorkIplabel * iplink_;
};


NetworkList::NetworkList(QWidget * parent)
    : BaseDialog(parent), d(new NetworkList::Private(this))
{
    //QString const style = theSkin()->styleSheet();
    //loadStyleSheet(this, style);
	d->ui.setupUi(this);
    //setModal(true);
	//setFixedSize(811, 486);
	QVBoxLayout * mainLayout = new QVBoxLayout;
	mainLayout->addWidget(d->ui.tableView_network_list);
	setLayout(mainLayout);

    d->network_list_model_ = new QStandardItemModel(this);
	QStringList labels;
    labels << tr("Signal Detection")
           << tr("Track Detection")
           << tr("Tunnel Detection")
           << tr("Contact-Net Dectection");

	d->network_list_model_->setHorizontalHeaderLabels(labels);
	d->ui.tableView_network_list->setModel(d->network_list_model_);
    d->ui.tableView_network_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//setResiziMode
	d->ui.tableView_network_list->verticalHeader()->setVisible(false);
    //d->ui.tableView_network_list->setSelectionMode(QAbstractItemView::SingleSelection);
	d->ui.tableView_network_list->setContextMenuPolicy(Qt::CustomContextMenu);

	d->iplink_ = new NetWorkIplabel;
	d->ui.tableView_network_list->setItemDelegateForColumn(3, d->iplink_);
 	d->ui.tableView_network_list->setMouseTracking(true); 

    installEventFilter(this);
	connect(d->ui.tableView_network_list, SIGNAL(customContextMenuRequested(const QPoint &)),
		this, SLOT(copyData()));
    //connect(this, SIGNAL(finished()), this, SLOT(showHpavList()));
}


NetworkList::~NetworkList()
{
    delete d;
}


void NetworkList::Private::fillNetworkList()
{/*
	m_data.clear();
    count_ = 0;

            int const current_row = network_list_model_->rowCount();
			network_list_model_->insertRows(current_row, 1);

            QString const mac = "708BCD7BE414";
            QStandardItem * header_item = new QStandardItem(mac);
			network_list_model_->setItem(current_row, 0, header_item);
 		    header_item->setToolTip(mac);

            QString device_model = "Standalone";

            QString qsName = "";
			if (qsName.isEmpty())
				qsName = tr("Remote adapter %n", "", count_+1);

            network_list_model_->setItem(current_row, 1, new QStandardItem(qsName.toStdString().c_str()));
            network_list_model_->setItem(current_row, 2, new QStandardItem(device_model));
			//network_list_model_->setItem(current_row, 3, new QStaticStandardItem(lea_firmware_.c_str()));
			network_list_model_->item(current_row, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			network_list_model_->item(current_row, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			network_list_model_->item(current_row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			//network_list_model_->item(current_row, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
*/
    //p_->GetFirmware();
	ui.tableView_network_list->resizeRowsToContents();
}


void NetworkList::GetFirmware()
{
    QtConcurrent::run<void, NetworkList>(this, &NetworkList::QthreadFirmware);
}


void NetworkList::QthreadFirmware()
{
    string ip = "192.168.1.1";
    string lea_firmware_ = "N/A";
    ip.empty()?m_data.append("unavailable"):m_data.append(ip.c_str());

    d->network_list_model_->setItem(count_, 4, new QStandardItem(lea_firmware_.c_str()));
    d->network_list_model_->item(count_++, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	finished();
}


void NetworkList::showHpavList()
{
    //d->loadImage_->hide();
	QDialog::show();
}


void NetworkList::show()
{
    d->fillNetworkList();

    QDialog::show();
}


void NetworkList::copyData()
{
	int maxCol=0, maxRow=0, minCol=0, minRow=0;
	int count = 0;
	QMap<QString, QString> map;
	QModelIndexList indexes = 
		d->ui.tableView_network_list->selectionModel()->selectedIndexes();
	if(0 == indexes.count())	
		return;
	QModelIndex index;
	foreach(index, indexes){
		int col = index.column();
		int row = index.row();
		if(0 == count++){
			minCol=col;
			minRow=row;
		}
		if(col > maxCol)	
			maxCol=col;
		if(row > maxRow)	
			maxRow=row;
		QString text = index.model()->data(index, Qt::EditRole).toString();
		map[QString::number(row)+","+QString::number(col)] = text;
	}
	QString rs = "";
	for(int row = minRow; row <= maxRow; row++){
		for (int col = minCol; col <= maxCol; col++){
			if(col != minCol)	rs+="\t";
			rs+=map[QString::number(row)+","+QString::number(col)];
		}
		rs+="\r\n";
	}
	QClipboard * board = QApplication::clipboard();
	board->setText(rs);
}


