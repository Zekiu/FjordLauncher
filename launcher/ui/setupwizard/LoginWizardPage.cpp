#include "LoginWizardPage.h"
#include "minecraft/auth/AccountList.h"
#include "ui/dialogs/AuthlibInjectorLoginDialog.h"
#include "ui_LoginWizardPage.h"

#include "Application.h"

LoginWizardPage::LoginWizardPage(QWidget* parent) : BaseWizardPage(parent), ui(new Ui::LoginWizardPage)
{
    ui->setupUi(this);
}

LoginWizardPage::~LoginWizardPage()
{
    delete ui;
}

void LoginWizardPage::initializePage() {}

bool LoginWizardPage::validatePage()
{
    return true;
}

void LoginWizardPage::retranslate()
{
    ui->retranslateUi(this);
}

void LoginWizardPage::on_pushButton_clicked()
{
    wizard()->hide();
    auto account = AuthlibInjectorLoginDialog::newAccount(nullptr, tr("Wpisz swój login (może się różnić od twojego nicku, pamiętaj!) oraz hasło."
                 "<br>"
                 "W trzecim polu wpisz <code>drasl.zekiu.xyz</code>, jeśli chcesz się zalogować na moją (Zekiu) instancję Drasl"));

    wizard()->show();
    if (account) {
        APPLICATION->accounts()->addAccount(account);
        APPLICATION->accounts()->setDefaultAccount(account);
        if (wizard()->currentId() == wizard()->pageIds().last()) {
            wizard()->accept();
        } else {
            wizard()->next();
        }
    }
}
