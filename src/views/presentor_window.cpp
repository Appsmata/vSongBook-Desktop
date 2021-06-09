#include "presentor_window.h"
#include "ui_presentor_window.h"
#include <utils/app_utils.h>
#include <services/app_preferences.h>

int appTheme, fontSizePresent, fontSizePresentType, selectedSong, slides, slideno, slideIndex;
std::vector<QString> songverses1, songverses2, labels;
QFont PresentPreview, PresentFont;
bool isPresentBold, hasChorus;
QString slide, chorus;
Song song;
QIcon iconSmaller, iconBigger, iconDown, iconUp;

PresentorWindow::PresentorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PresentorWindow)
{
    ui->setupUi(this);

	setUpStuff();
    loadSettings();
    loadControls();
    requestData();
}

PresentorWindow::~PresentorWindow()
{
    delete ui;
}

void PresentorWindow::setUpStuff()
{

	if (!prefTabletMode::get())
	{
		ui->btnClose->hide();
	}
}

void PresentorWindow::loadSettings()
{
	appTheme = prefTheme::get();
	fontSizePresent = prefPresentFontSize::get();
	fontSizePresentType = prefPresentFontType::get();

	PresentPreview.setFamily(PrefUtils::preferencesFontTypes()[prefPreviewFontType::get()]);
	PresentPreview.setPointSize(prefPreviewFontSize::get());
	PresentPreview.setBold(prefPreviewFontBold::get());
	PresentPreview.setWeight(50);

	PresentFont.setFamily(PrefUtils::preferencesFontTypes()[fontSizePresentType]);
	PresentFont.setPointSize(prefPresentFontSize::get());
	PresentFont.setBold(prefPresentFontBold::get());
	PresentFont.setWeight(50);
}

void PresentorWindow::loadTheme()
{
	switch (appTheme)
	{
		case 2:
			ui->centralwidget->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
			ui->statusBar->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
			loadButtonIcons(false);
			break;

		case 3:
			ui->centralwidget->setStyleSheet("* { background-color: #A9A9A9; color: #FFFFFF; }");
			ui->statusBar->setStyleSheet("* { background-color: #A9A9A9; color: #FFFFFF; }");
			loadButtonIcons(true);
			break;

		case 4:
			ui->centralwidget->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
			ui->statusBar->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
			loadButtonIcons(false);
			break;

		case 5:
			ui->centralwidget->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");
			ui->statusBar->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");
			loadButtonIcons(true);
			break;

		case 6:
			ui->centralwidget->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");
			ui->statusBar->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");
			loadButtonIcons(false);
			break;

		case 7:
			ui->centralwidget->setStyleSheet("* { background-color: #006400; color: #FFFFFF; }");
			ui->statusBar->setStyleSheet("* { background-color: #006400; color: #FFFFFF; }");
			loadButtonIcons(true);
			break;

		case 8:
			ui->centralwidget->setStyleSheet("* { background-color: #FFFFFF; color: #006400; }");
			ui->statusBar->setStyleSheet("* { background-color: #FFFFFF; color: #006400; }");
			loadButtonIcons(false);
			break;

		case 9:
			ui->centralwidget->setStyleSheet("* { background-color: #FFA500; color: #000000; }");
			ui->statusBar->setStyleSheet("* { background-color: #FFA500; color: #000000; }");
			loadButtonIcons(true);
			break;

		case 10:
			ui->centralwidget->setStyleSheet("* { background-color: #000000; color: #FFA500; }");
			ui->statusBar->setStyleSheet("* { background-color: #000000; color: #FFA500; }");
			loadButtonIcons(false);
			break;

		case 11:
			ui->centralwidget->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");
			ui->statusBar->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");
			loadButtonIcons(true);
			break;

		case 12:
			ui->centralwidget->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");
			ui->statusBar->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");
			loadButtonIcons(false);
			break;

		case 13:
			ui->centralwidget->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");
			ui->statusBar->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");
			loadButtonIcons(true);
			break;

		case 14:
			ui->centralwidget->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");
			ui->statusBar->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");
			loadButtonIcons(false);
			break;

		default:
			ui->centralwidget->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
			ui->statusBar->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
			loadButtonIcons(true);
			break;

	}
}

void PresentorWindow::loadButtonIcons(bool light)
{
	iconSmaller.detach();
	iconBigger.detach();
	iconUp.detach();
	iconDown.detach();

	if (light)
	{
		iconSmaller.addFile(QString::fromUtf8(":/images/Smaller_White.png"), QSize(), QIcon::Normal, QIcon::Off);
		iconBigger.addFile(QString::fromUtf8(":/images/Bigger_White.png"), QSize(), QIcon::Normal, QIcon::Off);
		iconUp.addFile(QString::fromUtf8(":/images/Up_White.png"), QSize(), QIcon::Normal, QIcon::Off);
		iconDown.addFile(QString::fromUtf8(":/images/Down_White.png"), QSize(), QIcon::Normal, QIcon::Off);
	}
	else
	{
		iconSmaller.addFile(QString::fromUtf8(":/images/Smaller_Black.png"), QSize(), QIcon::Normal, QIcon::Off);
		iconBigger.addFile(QString::fromUtf8(":/images/Bigger_Black.png"), QSize(), QIcon::Normal, QIcon::Off);
		iconUp.addFile(QString::fromUtf8(":/images/Up_Black.png"), QSize(), QIcon::Normal, QIcon::Off);
		iconDown.addFile(QString::fromUtf8(":/images/Down_Black.png"), QSize(), QIcon::Normal, QIcon::Off);
	}

	ui->btnSmaller->setIcon(iconSmaller);
	ui->btnBigger->setIcon(iconBigger);
	ui->btnUp->setIcon(iconUp);
	ui->btnDown->setIcon(iconDown);
}

void PresentorWindow::loadControls()
{
	ui->lblTitle->setFont(PresentFont);
	ui->lblContent->setFont(PresentFont);
	ui->lblSongbook->setFont(PresentPreview);
	ui->lblAuthor->setFont(PresentPreview);
	ui->lblVerse->setFont(PresentPreview);
	loadTheme();
}

void PresentorWindow::requestData()
{
	selectedSong = prefSelectedSong::get();
	if (selectedSong > 0)
	{
		appDb->connectionOpen("present_song");
		song = appDb->fetchSong(selectedSong);
		appDb->connectionClose("present_song");
		if (song.title.length() > 0) presentSong();
	}
}

void PresentorWindow::presentSong()
{
	slides = 0;
	if (songverses1.size() > 0) songverses1.clear();
	if (songverses2.size() > 0) songverses2.clear();

	if (song.content.contains("CHORUS")) hasChorus = true;
	else hasChorus = false;

	QStringList tokens = song.content.split("\\n\\n");

	if (tokens.length() > 1)
	{
		for (int i = 0; i < tokens.length(); i++)
		{
			QString token = tokens[i];
			if (hasChorus)
			{
				if (token.contains("CHORUS")) chorus = token.replace("CHORUS\\n", "");
				else songverses1.push_back(token);
			}
			else songverses2.push_back(token);
		}
	}

	if (hasChorus)
	{
		int k = 1;
		for (std::vector<QString>::iterator i = songverses1.begin(); i != songverses1.end(); ++i)
		{
			songverses2.push_back(*i);
			songverses2.push_back(chorus);
			slides = slides + 2;

			QString label = "VERSE " + QString::number(k);
			label.append(" / " + QString::number(songverses1.size()));
			labels.push_back(label);
			labels.push_back("CHORUS ");
			k++;
		}
	}
	else slides = songverses2.size();
	slideIndex = 0;
	setPresentation();
}

void PresentorWindow::setPresentation()
{
	slideno = slideIndex + 1;
	slide = songverses2[slideIndex];
	ui->lblTitle->setText(AppUtils::replaceView(QString::number(song.number) + "# " + song.title));
	ui->lblContent->setText(AppUtils::replaceView(slide));
	ui->lblAuthor->setText(song.author);
	ui->lblKey->setText("Key: " + song.key);
	ui->lblSongbook->setText(song.book);
	ui->lblVerse->setText(labels[slideIndex]);

	if (slideIndex == 0)
	{
		ui->btnUp->hide();
		ui->btnDown->show();
	}

	else if (slideIndex == (slides - 1))
	{
		ui->btnUp->show();
		ui->btnDown->hide();
	}

	else
	{
		ui->btnUp->show();
		ui->btnDown->show();
	}
}

void PresentorWindow::themeChange()
{
	switch (appTheme)
	{
		case 15:
			appTheme = 1;
			break;

		default:
			appTheme = appTheme + 1;
			break;
	}
	prefTheme::set(appTheme);
	loadSettings();
	loadControls();
}

// Changing of font of the song present
void PresentorWindow::fontChange()
{
	switch (fontSizePresentType)
	{
		case 12:
			fontSizePresentType = 1;
			break;

		default:
			fontSizePresentType = fontSizePresentType + 1;
			break;
	}
	prefPresentFontType::set(fontSizePresentType);
	loadSettings();
	loadControls();
}

// Reduce Present Font Size
void PresentorWindow::fontSmaller()
{
	if ((fontSizePresent - 2) > 9)
	{
		fontSizePresent = fontSizePresent - 2;
		PresentFont.setPointSize(fontSizePresent);
		prefPresentFontSize::set(fontSizePresent);
		loadSettings();
		loadControls();
	}
}

void PresentorWindow::fontBigger()
{
	if ((fontSizePresent + 2) < 51)
	{
		fontSizePresent = fontSizePresent + 2;
		prefPresentFontSize::set(fontSizePresent);
		loadSettings();
		loadControls();
	}
}

void PresentorWindow::fontBold()
{
	if (isPresentBold) isPresentBold = false;
	else isPresentBold = true;
	prefPresentFontBold::set(isPresentBold);
	loadSettings();
	loadControls();
}

void PresentorWindow::previousVerse()
{
	if (slideIndex != 0)
	{
		slideIndex = slideIndex - 1;
		setPresentation();
	}
}

void PresentorWindow::nextVerse()
{
	if (slideIndex != (slides - 1))
	{
		slideIndex = slideIndex + 1;
		setPresentation();
	}
}

void PresentorWindow::on_btnClose_clicked()
{
    close();
}

void PresentorWindow::on_actionClose_triggered()
{
    close();
}

void PresentorWindow::on_actionFont_triggered()
{
    fontChange();
}

void PresentorWindow::on_actionBold_triggered()
{
    fontBold();
}

void PresentorWindow::on_actionSmaller_triggered()
{
    fontSmaller();
}

void PresentorWindow::on_actionBigger_triggered()
{
    fontBigger();
}

void PresentorWindow::on_actionUp_triggered()
{
	previousVerse();
}

void PresentorWindow::on_actionDown_triggered()
{
	nextVerse();
}

void PresentorWindow::on_btnBold_clicked()
{
	fontBold();
}

void PresentorWindow::on_btnFont_clicked()
{
	fontChange();
}

void PresentorWindow::on_btnBigger_clicked()
{
	fontBigger();
}

void PresentorWindow::on_btnSmaller_clicked()
{
	fontSmaller();
}

void PresentorWindow::on_btnUp_clicked()
{
	previousVerse();
}

void PresentorWindow::on_btnDown_clicked()
{
	nextVerse();
}

void PresentorWindow::on_btnTheme_clicked()
{
	themeChange();
}

void PresentorWindow::on_actionTheme_triggered()
{
	themeChange();
}
