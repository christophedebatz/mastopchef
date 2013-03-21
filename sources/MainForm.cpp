#include "MainForm.h"

using namespace std;


// djeb2003@yahoo.fr

MainForm::MainForm()
{
    // main details
    setWindowTitle("MASTOP CHEF");
    setFixedSize(750, 600);
    setWindowIcon(QIcon("pictures/logo.png"));
    logo = new QLabel;
    logo->setPixmap(QPixmap("pictures/logo.png"));

    // show main menu and tabs
    createMenu();
    createTabs();

    // order widgets and create layout
    centeredZone = new QWidget; // centrale zone
    setCentralWidget(centeredZone);

    mainGridLayout = new QGridLayout;
    mainGridLayout->addWidget(tabs, 0, 0, 2, 1);
    mainGridLayout->addWidget(logo, 0, 1);
    centeredZone->setLayout(mainGridLayout);

    // show search area and tabs inside
    createSearchQuarter();
    createTabsComponents();

    // show the form
    show();
}



/**
*  createMenu : draw the main menu
*
*   @param  void
*   @return void
*
*/
void MainForm::createMenu()
{
    QMenu *menuFile = menuBar()->addMenu("&Fichier");
        QMenu *subMenuNew = menuFile->addMenu("&Nouveau");
            subMenuNew->setIcon(QIcon("pictures/icons/document-new.png"));
            QAction *actionNewRecipe = subMenuNew->addAction("Recette");
            actionNewRecipe->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
            QAction *actionNewIngredient = subMenuNew->addAction("Ingredient");
            actionNewIngredient->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
            QAction *actionNewMaterial = subMenuNew->addAction("Matériel");
            actionNewMaterial->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
            QAction *actionNewUnit = subMenuNew->addAction("Unité");
            actionNewUnit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
            QAction *actionNewAction = subMenuNew->addAction("Action");
            actionNewAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
        QAction *subMenuOpenRecipe = menuFile->addAction("&Ouvrir...");
            subMenuOpenRecipe->setIcon(QIcon("pictures/icons/document-open.png"));
            subMenuOpenRecipe->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
        QAction *subMenuQuit = menuFile->addAction("&Quitter");
            subMenuQuit->setIcon(QIcon("pictures/icons/system-log-out.png"));
            subMenuQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));

    QMenu *menuAbout = menuBar()->addMenu("&A Propos");
        QAction *actionAbout = menuAbout->addAction("&A propos...");
            actionAbout->setIcon(QIcon("pictures/icons/system-users.png"));
            actionAbout->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
        QAction *actionHelp = menuAbout->addAction("&Aide");
            actionHelp->setIcon(QIcon("pictures/icons/help-browser.png"));
            actionHelp->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));


    connect(actionNewIngredient, SIGNAL(triggered()), this, SLOT(openAddNewIngredient()));
    connect(actionNewUnit, SIGNAL(triggered()), this, SLOT(openManageUnities()));
    connect(actionNewMaterial, SIGNAL(triggered()), this, SLOT(openAddMaterial()));
    connect(actionNewRecipe, SIGNAL(triggered()), this, SLOT(openAddNewRecipe()));
    connect(actionNewAction, SIGNAL(triggered()), this, SLOT(openManageActions()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(openAbout()));
    connect(subMenuOpenRecipe, SIGNAL(triggered()), this, SLOT(openRecipe()));
    connect(subMenuQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
}



/**
*  createTabs : draw the tabs
*
*   @param  void
*   @return void
*
*/
void MainForm::createTabs()
{
    tabs = new QTabWidget(this);
    tabs->setGeometry(10, 30, 650, 535);

    tabGeneral = new QWidget;
    tabIngredients = new QWidget;
    tabPreparation = new QWidget;

    tabs->addTab(tabGeneral, "General");
    tabs->addTab(tabIngredients, "Ingredients");
    tabs->addTab(tabPreparation, "Preparation");
}





void MainForm::openRecipe()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choisissez une recette...", "./", "Recette Mastop Chef (*.rcp)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly))
            speedDialog("c", "Erreur", "Impossible d'ouvrir la recette !");
        QString content = file.readAll();
        file.close();

        // split and get informations
        QStringList first = content.split("**");
        QStringList ingr = first[5].split("||"); // ingredients
        QStringList steps = first[6].split("||"); // etapes

        QString stepsStr = "<br /><center><h2>ETAPES DE LA RECETTE</h2></center><hr /><ul>";
        for (int i = 0; i < steps.length(); i++)
            stepsStr += "<li> " + steps[i] + "</li>";

        stepsStr += "</ul>";
        this->recipePrepare->setProperty("text", stepsStr);


        QString ingrStr = "<br /><center><h2>INGREDIENTS DE LA RECETTE</h2></center><hr /><ul>";
        for (int i = 0; i < ingr.length(); i++)
            ingrStr += "<li> " + ingr[i] + "</li>";

        ingrStr += "</ul>";
        this->recipeIngr->setProperty("text", ingrStr);

        QString generalStr = "<br /><center><h2>INFORMATIONS GLOBALES SUR LA RECETTE</h2><h3>" + first[0] + "</h3></center><hr />";
        generalStr += "<ul><li> NOM : <b>" + first[0] + "</b></li>";
        generalStr += "<li> CONVIVES : <b>" + first[1] + " personne(s)</b></li>";
        generalStr += "<li> PREPARATION : <b>" + first[2] + " minute(s)</b></li>";
        generalStr += "<li> DIFFICULTE : <b>" + first[3] + "</b></li></ul>";

        this->recipeGeneral->setProperty("text", generalStr);
        this->layoutSearch->addWidget(recipeImage);

        if (first[4] == "none")
            this->recipeImage->setPixmap(QPixmap("pictures/nopic.png"));
        else
            this->recipeImage->setPixmap(QPixmap("res/recipes/pictures/" + first[4]));
    }
}// nom**capacite**difficulte**image**ingr...**etapes...





/**
*  createTabsComponents : draw the tabs components
*
*   @param  void
*   @return void
*
*/
void MainForm::createTabsComponents()
{
    recipeGeneral = new QLabel("");
    recipeImage = new QLabel("");
    recipeIngr = new QLabel("");
    recipePrepare = new QLabel("");

    layoutGeneral = new QHBoxLayout;
    layoutIngr = new QHBoxLayout;
    layoutPrepare = new QHBoxLayout;

    tabIngredients->setLayout(layoutIngr);
    layoutIngr->setAlignment(Qt::AlignTop);
    tabPreparation->setLayout(layoutPrepare);
    layoutPrepare->setAlignment(Qt::AlignTop);
    tabGeneral->setLayout(layoutGeneral);
    layoutGeneral->setAlignment(Qt::AlignTop);

    layoutGeneral->addWidget(recipeGeneral);
    layoutIngr->addWidget(recipeIngr);
    layoutPrepare->addWidget(recipePrepare);

    this->recipeGeneral->setProperty("text", "<hr /><br /><center><h2 style=\"color: #964f36;\">Veuillez ouvrir une recette...</h2></center><br /><hr />");
    this->recipeIngr->setProperty("text", "<hr /><br /><center><h2 style=\"color: #964f36;\">Veuillez ouvrir une recette...</h2></center><br /><hr />");
    this->recipePrepare->setProperty("text", "<hr /><br /><center><h2 style=\"color: #964f36;\">Veuillez ouvrir une recette...</h2></center><br /><hr />");
}



/**
*  createSearchQuarter : draw the search rectangle
*
*   @param  void
*   @return void
*
*/
void MainForm::createSearchQuarter()
{
    groupSearch = new QGroupBox(" Illustration ", this);
    mainGridLayout->addWidget(groupSearch, 1, 1);
    layoutSearch = new QHBoxLayout;
    groupSearch->setLayout(layoutSearch);
    layoutSearch->setAlignment(Qt::AlignCenter);
}



void MainForm::openAddNewRecipe()
{
    addRecipeDialog = new QDialog(this);
    addRecipeDialog->setModal(true);
    addRecipeDialog->setFixedSize(560, 600); // resize
    addRecipeDialogLayout = new QVBoxLayout; // main vertical layout

    // paint the logo of dialog
    pictureRecipe = new QLabel;
    pictureRecipe->setPixmap(QPixmap("pictures/recipe.png"));
    addRecipeDialogLayout->addWidget(pictureRecipe);
    pictureRecipe->setAlignment(Qt::AlignTop);

    groupAddRecipe1 = new QGroupBox(" Paramètres généraux ", this);
    addRecipeDialogLayout->addWidget(groupAddRecipe1);

    // gridlayout groupbox
    addRecipeMiddleLayout = new QHBoxLayout;
    addRecipeLayout = new QFormLayout;
    rNameInput = new QLineEdit;
    rCapacityInput = new QSpinBox;
    rCapacityInput->setMinimum(1);
    rCapacityInput->setMaximum(99);
    rDifficultyInput = new QComboBox(this);
    rDifficultyInput->addItem("Très facile");
    rDifficultyInput->addItem("Plutôt Facile");
    rDifficultyInput->addItem("Moyennement simple");
    rDifficultyInput->addItem("Plutôt difficile");
    rDifficultyInput->addItem("Difficile");
    setImageRecipe = new QPushButton(" Parcourir... ");
    imageRecipePath = new QLabel("Veuillez choisir une image");

    addRecipeLayout->addRow("Nom de la recette : ", rNameInput);
    addRecipeLayout->addRow("Nombre de convives : ", rCapacityInput);
    addRecipeLayout->addRow("Difficulté de réalisation : ", rDifficultyInput);
    addRecipeLayout->addRow("Image associée (130x130) : ", setImageRecipe);
    addRecipeLayout->addRow(" ", imageRecipePath);

    addRecipeMiddleLayout->addLayout(addRecipeLayout);
    // image of recipe
    recipeImage = new QLabel;
    recipeImage->setPixmap(QPixmap("pictures/nopic.png"));
    recipeImage->setAlignment(Qt::AlignTop);
    addRecipeMiddleLayout->addWidget(recipeImage);

    // ingredients
    groupAddRecipe2 = new QGroupBox(" Ingrédient(s) ");
    addRecipeIngredientLayout = new QGridLayout;

    addIngredientToRecipe = new QPushButton(" Ajouter... ");
    addRecipeIngredientLayout->addWidget(addIngredientToRecipe, 0, 0);

    removeIngredientToRecipe = new QPushButton(" Supprimer ");
    addRecipeIngredientLayout->addWidget(removeIngredientToRecipe, 1, 0);

    groupAddRecipe2->setLayout(addRecipeIngredientLayout);
    addRecipeDialogLayout->addWidget(groupAddRecipe2);

    // cooking protocol
    groupAddRecipe3 = new QGroupBox(" Etape(s) de la recette ");
    addRecipeProtocolLayout = new QGridLayout;

    addStep = new QPushButton(" Ajouter... ");
    addRecipeProtocolLayout->addWidget(addStep, 0, 0);

    removeStep = new QPushButton(" Supprimer ");
    addRecipeProtocolLayout->addWidget(removeStep, 1, 0);

    listSteps = new QListWidget(this);
    listSteps->setFixedHeight(150);
    addRecipeProtocolLayout->addWidget(listSteps, 0, 1, 4, 1);

    // build the list of ingredients
    updateIngredientsAssociated();

    groupAddRecipe3->setLayout(addRecipeProtocolLayout);
    addRecipeDialogLayout->addWidget(groupAddRecipe3);

    // cancel & submit.. buttons
    addRecipeBottomLayout = new QHBoxLayout;
    addRecipeBottomLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    addRecipeCancel = new QPushButton(" Annuler ");
    submitRecipe = new QPushButton(" Ajouter ");
    addRecipeBottomLayout->addWidget(addRecipeCancel);
    addRecipeBottomLayout->addWidget(submitRecipe);
    addRecipeDialogLayout->addLayout(addRecipeBottomLayout);

    groupAddRecipe1->setLayout(addRecipeMiddleLayout);
    addRecipeDialog->setLayout(addRecipeDialogLayout);
    addRecipeDialog->show();


    connect(setImageRecipe, SIGNAL(clicked()), this, SLOT(chooseImageRecipe()));
    connect(addStep, SIGNAL(clicked()), this, SLOT(openAddCookStep())); // open add step recipe
    connect(addIngredientToRecipe, SIGNAL(clicked()), this, SLOT(openAssocIngrRecipeDialog())); // add an ingredient to the current recipe
    connect(addRecipeCancel, SIGNAL(clicked()), this, SLOT(closeAddRecipeDialog()));
    connect(removeIngredientToRecipe, SIGNAL(clicked()), this, SLOT(removeIngr()));
    connect(removeStep, SIGNAL(clicked()), this, SLOT(removeStepToRecipe()));
    connect(submitRecipe, SIGNAL(clicked()), this, SLOT(submitRecipeMethod()));
}




void MainForm::submitRecipeMethod()
{
    if (this->rNameInput->text() == QString("")) {
        speedDialog("w", "Incomplet", "Vous devez donner un nom à la recette !");
        return;
    }

    if (cookSteps.size() == 0) {
        speedDialog("w", "Incomplet", "Vous devez ajouter au moins une étape !");
        return;
    }



    QString picName = "none";
    if (this->imageRecipePath->text() != "Veuillez choisir une image") {
        picName = QFileInfo(this->imageRecipePath->text()).fileName();
        if (!QFile::copy(this->imageRecipePath->text(), "res/recipes/pictures/" + picName))
            speedDialog("c", "Copie impossible", "Impossible de copier l'image");
    }


    int totalTime = 0;
    QString steps = "";
    list<CookStep>::iterator it1;
    for (it1 = cookSteps.begin(); it1 != cookSteps.end(); ++it1)
        totalTime += (int) (*it1).getTime();


    QString sep = "||";
    for (int i = 0; i < this->listSteps->count(); i++){
        if (i == this->listSteps->count() - 1) sep = "";
        steps += this->listSteps->item(i)->text().toAscii().data()+ sep;
    }


    QString ingr;
    vector<Ingredient>::iterator it2;
    for (it2 = ingredients.begin(); it2 < ingredients.end(); ++it2)
        ingr += QString::fromStdString((*it2).getName()) + "||";




    QFile file("res/recipes/" + this->rNameInput->text() + ".rcp");
    if (!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);

    out << this->rNameInput->text() + "**"
        + QString::number(this->rCapacityInput->value()) + "**"
        + QString::number(totalTime) + "**"
        + this->rDifficultyInput->currentText() + "**"
        + picName + "**"
        + ingr + "**"
        + steps;

    file.close();
/*Recipe rcp(this->rNameInput->text().toStdString(),
               this->rCapacityInput->value(),
               this->rDifficultyInput->currentText().toStdString(),
               this->imageRecipePath->text().toStdString(),
               ingredients,
               cookSteps);*/
    //recipe->save();


    speedDialog("i", "Recette ajoutée", "La recette <b>" + this->rNameInput->text().toStdString() + "</b><br />vient d'être ajoutée !<br /><br />La fenêtre va se fermer...");
    closeAddRecipeDialog();
}




void MainForm::openAssocIngrRecipeDialog()
{
    ingrToRecipeDialog = new QDialog(this);
    ingrToRecipeDialog->setModal(true);
    ingrToRecipeDialog->setFixedSize(315, 160); // resize

    ingrToRecipeVLayout = new QVBoxLayout; // main vertical layout
    ingrToRecipeBox = new QGroupBox(" Associer un ingrédient à une recette ");
    ingrToRecipeGridLayout = new QGridLayout;

    //generate unity and names combobox...
    ingrListUnit = new QComboBox(this);
    ingrListName = new QComboBox(this);
    openAddIngredientDialog = new QPushButton(" Ajouter un ingrédient ");
    ingrQuantity = new QDoubleSpinBox();
    ingrQuantity->setMinimum(0.05);
    ingrQuantity->setDecimals(2);
    ingrQuantity->setMaximum(999);
    ingrNameLabel = new QLabel("Nom de l'ingrédient : ");
    ingrQuantityLabel = new QLabel("Quantité désirée : ");

    // fill ingredient QComboBox
    ingrListName->addItems(getListOfFiles());

    // get the unities of the first ingredient
    getUnitsFromIngredient(ingrListName->currentText());

    ingrToRecipeGridLayout->addWidget(ingrNameLabel, 0, 0);
    ingrToRecipeGridLayout->addWidget(ingrListName, 0, 1, 1, 2);
    ingrToRecipeGridLayout->addWidget(openAddIngredientDialog, 1, 1, 1, 2);
    ingrToRecipeGridLayout->addWidget(ingrQuantityLabel, 2, 0, 1, 2);
    ingrToRecipeGridLayout->addWidget(ingrQuantity, 2, 1);
    ingrToRecipeGridLayout->addWidget(ingrListUnit, 2, 2);

    ingrToRecipeBox->setLayout(ingrToRecipeGridLayout);
    ingrToRecipeVLayout->addWidget(ingrToRecipeBox); // add groupbox to verticalLayout

    // val and cancel buttons
    ingrToRecipeBottomLayout = new QHBoxLayout;
    ingrToRecipeCancel = new QPushButton("Annuler");
    ingrToRecipeBottomLayout->addWidget(ingrToRecipeCancel);
    ingrToRecipeValidate = new QPushButton(" Associer ");
    ingrToRecipeBottomLayout->addWidget(ingrToRecipeValidate);
    ingrToRecipeBottomLayout->setAlignment(Qt::AlignRight);
    ingrToRecipeVLayout->addLayout(ingrToRecipeBottomLayout);

    ingrToRecipeDialog->setLayout(ingrToRecipeVLayout);
    ingrToRecipeDialog->show();

    connect(ingrListName, SIGNAL(currentIndexChanged(QString)), this, SLOT(getUnitsFromIngredient(QString))); // check which unities can be used
    connect(ingrToRecipeCancel, SIGNAL(clicked()), this, SLOT(closeAssocIngrRecipeDialog())); // close the dialog
    connect(ingrToRecipeValidate, SIGNAL(clicked()), this, SLOT(applyIngrRecipeAssoc())); // apply and save the ingredient association
    connect(openAddIngredientDialog, SIGNAL(clicked()), this, SLOT(openAddNewIngredient())); // open new Ingredient dialog
}




QStringList MainForm::getActionsFromMaterial(const QString& materialName)
{
    QFile file("res/material/" + materialName + ".mat");
    if (!file.open(QFile::ReadOnly))
        speedDialog("c", "Erreur", "Impossible d'accéder au matériel.");
    QString content = file.readAll();
    file.close();

    // split and get ingredient's name
    QStringList materialDetails = content.split("**");
    return materialDetails[1].split("||");
}




void MainForm::getUnitsFromIngredient(const QString& ingredientName)
{
    QFile file("res/ingredients/" + ingredientName + ".ingr");
    if (!file.open(QFile::ReadOnly))
        speedDialog("c", "Erreur", "Impossible d'accéder à l'ingrédient.");
    QString content = file.readAll();
    file.close();

    // split and get ingredient's name
    QStringList ingrDetails = content.split("**");
    this->ingrListUnit->clear();
    this->ingrListUnit->addItems(ingrDetails[1].split("||"));
}



void MainForm::applyIngrRecipeAssoc()
{
    Ingredient tempIngr(this->ingrListName->currentText().toStdString());
    tempIngr.setQuantity(this->ingrQuantity->value());
    tempIngr.setUnit(this->ingrListUnit->currentText().toStdString());

    // check if ingredient has already been associated
    vector<Ingredient>::iterator it;
    bool alreadyAdded = false;
    for (it = ingredients.begin(); it < ingredients.end(); ++it){
        if ((*it).getName() == this->ingrListName->currentText().toStdString())
            alreadyAdded = true;
    }

    // if current ingredient is not already here, we add it
    if (!alreadyAdded)
        ingredients.push_back(tempIngr);
    else{
        speedDialog("w", "Association impossible", "Cet ingrédient a déjà été associé à la recette en cours.<br />Supprimez-le avant de le ré-associer...");
        return;
    }

    addRecipeIngredientLayout->removeWidget(listIngredients);
    delete listIngredients;

    updateIngredientsAssociated(); // update the associated ingredients list
    closeAssocIngrRecipeDialog(); // close over-dialogbox
}



void MainForm::updateIngredientsAssociated()
{
    QStringList ingredientsList;
    listIngredients = new QListWidget(this);
    listIngredients->setFixedHeight(55);

    if (ingredients.size() == 0){// enabled or disabled removing button if there is or there is no associated ingredients
        this->removeIngredientToRecipe->setDisabled(true);
        this->groupAddRecipe3->setDisabled(true);
        this->listSteps->clear();
    }
    else{
        this->removeIngredientToRecipe->setDisabled(false);
        this->groupAddRecipe3->setDisabled(false);
    }

    for (unsigned i = 0; i < ingredients.size(); i++)
        ingredientsList << QString::number(ingredients[i].getQuantity(), 'f', 2) + " " + QString::fromStdString(ingredients[i].getUnit() == "-" ? " " : ingredients[i].getUnit() + " de ") + QString::fromStdString(ingredients[i].getName());

    listIngredients->addItems(ingredientsList);
    addRecipeIngredientLayout->addWidget(listIngredients, 0, 1, 2, 1);
    addRecipeIngredientLayout->setAlignment(Qt::AlignTop);


    this->addRecipeDialog->update(); // repaint the dialog
}



void MainForm::removeIngr()
{
    if (listIngredients->currentItem()){
        vector<Ingredient>::iterator it;

        for (it = ingredients.begin(); it < ingredients.end(); ++it){
            if (listIngredients->currentItem()->text() == QString::number((*it).getQuantity(), 'f', 2) + " " + QString::fromStdString((*it).getUnit() == "-" ? " " : (*it).getUnit() + " de ") + QString::fromStdString((*it).getName()))
                ingredients.erase(it);
        }
        delete listIngredients->currentItem();
        updateIngredientsAssociated();
    }
}



void MainForm::openAddCookStep()
{
    addStepDialog = new QDialog(this);
    addStepDialog->setModal(true);
    addStepDialog->setFixedSize(340, 220); // resize

    addStepVLayout = new QVBoxLayout; // main vertical layout
    addStepMainGroup = new QGroupBox(" Ajouter une étape de la recette ");
    addSTepGridLayout = new QGridLayout;

    actionLabel = new QLabel("Action de l'étape :");
    materialLabel = new QLabel("Matériel utilisé :");
    ingredientLabel = new QLabel("Ingrédient requis :");
    mediumIngrLabel = new QLabel("Ingredient résultant :");
    timeLabel = new QLabel("Temps nécessaire :");
    timeContent = new QSpinBox();
    selectActionRecipe = new QComboBox;
    selectMaterialRecipe = new QComboBox;
    selectIngrRecipe = new QComboBox;
    selectMediumIngrRecipe = new QComboBox;
    selectMediumIngrRecipe->setEditable(true);

    // on rempli la listbox des ingredients temporaires déjà rentrés
    vector<string>::iterator ite;
    for (ite = temporalyIngr.begin(); ite < temporalyIngr.end(); ++ite)
        selectMediumIngrRecipe->addItem(QString::fromStdString(*ite));

    addSTepGridLayout->addWidget(actionLabel, 0, 0);
    addSTepGridLayout->addWidget(ingredientLabel,1, 0);
    addSTepGridLayout->addWidget(materialLabel, 2, 0);
    addSTepGridLayout->addWidget(mediumIngrLabel, 3, 0);
    addSTepGridLayout->addWidget(selectActionRecipe, 0, 1);
    addSTepGridLayout->addWidget(selectIngrRecipe, 1, 1);
    addSTepGridLayout->addWidget(selectMaterialRecipe, 2, 1);
    addSTepGridLayout->addWidget(selectMediumIngrRecipe, 3, 1);
    addSTepGridLayout->addWidget(timeLabel, 4, 0);
    addSTepGridLayout->addWidget(timeContent, 4, 1);

    vector<Ingredient>::iterator it;

    for (it = ingredients.begin(); it < ingredients.end(); ++it)
        selectIngrRecipe->addItem(QString::number((*it).getQuantity(), 'f', 2) + " " + QString::fromStdString((*it).getUnit() == "-" ? " " : (*it).getUnit() + " de ") + QString::fromStdString((*it).getName()));

    selectActionRecipe->addItems(getListOfActionsMaterial("res/material"));
    selectMaterialRecipe->addItems(getMaterialFromAction(selectActionRecipe->currentText()));

    // components
    addStepMainGroup->setLayout(addSTepGridLayout);
    addStepVLayout->addWidget(addStepMainGroup); // add groupbox to verticalLayout

    // val and cancel buttons
    addStepBottomLayout = new QHBoxLayout;
    addStepCancel = new QPushButton("Annuler");
    addStepBottomLayout->addWidget(addStepCancel);
    addStepValidate = new QPushButton(" Ajouter ");
    addStepBottomLayout->addWidget(addStepValidate);
    addStepBottomLayout->setAlignment(Qt::AlignRight);
    addStepVLayout->addLayout(addStepBottomLayout);

    addStepDialog->setLayout(addStepVLayout);
    addStepDialog->show();

    // slots
    connect(selectActionRecipe, SIGNAL(currentIndexChanged(QString)), this, SLOT(getMaterialFromActionRefresh())); // check which unities can be used
    connect(addStepCancel, SIGNAL(clicked()), this, SLOT(closeAddStepDialog())); // check which unities can be used
    connect(addStepValidate, SIGNAL(clicked()), this, SLOT(addCookStepMethod()));
}



// on verifiera si tous les ingredients de la listes ont bien été utilisés à la fin (validation de la recette)

void MainForm::addCookStepMethod()
{
    // create ingredient and material occurences
    Ingredient ingr(this->selectIngrRecipe->currentText().toStdString());
    Material mat(this->selectMaterialRecipe->currentText().toStdString());

    // create a new step of the recipe
    CookStep cs(&ingr, &mat, this->selectActionRecipe->currentText().toStdString(), this->selectMediumIngrRecipe->currentText().toStdString(), this->timeContent->value());
    cookSteps.push_back(cs);

    if (this->selectMediumIngrRecipe->currentText() != "")
    {
        bool isHere = false;
        vector<string>::iterator ite;
        for (ite = temporalyIngr.begin(); ite < temporalyIngr.end(); ++ite) {
            if ((*ite) == this->selectMediumIngrRecipe->currentText().toStdString()) {
                isHere = true;
                break;
            }
        }

        if (!isHere)
            temporalyIngr.push_back(this->selectMediumIngrRecipe->currentText().toStdString());
    }

    // we add the step to the listbox
    this->listSteps->addItem(QString::fromStdString(cs.showString()));
    this->removeStep->setDisabled(false);
    this->addStepDialog->close();
}




void MainForm::removeStepToRecipe()
{

    if (this->listSteps->currentItem()){
        list<CookStep>::iterator it;

        for (it = cookSteps.begin(); it != cookSteps.end(); ++it){
            if (listSteps->currentItem()->text() == QString::fromStdString((*it).showString()))
                cookSteps.erase(it);
        }

        delete listSteps->currentItem();

        if (cookSteps.size() <= 0)
            this->removeStep->setDisabled(true);
    }
}



void MainForm::closeAddStepDialog()
{
    this->addStepDialog->close();
}





void MainForm::getMaterialFromActionRefresh()
{
    this->selectMaterialRecipe->clear();
    this->selectMaterialRecipe->addItems(getMaterialFromAction(this->selectActionRecipe->currentText()));
}





QStringList MainForm::getMaterialFromAction(const QString& action)
{
    QStringList result;

    QDir dir("res/material");
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dir.setNameFilters(QStringList() << "*.mat");

    foreach(QFileInfo fileInfo, dir.entryInfoList())
    {
        // open the ingredient file
        QFile file(fileInfo.absoluteFilePath());
        if (!file.open(QFile::ReadOnly))
            speedDialog("c", "Erreur", "Impossible d'accéder au fichier matériel.");
        QString content = file.readAll();

        QStringList content2 = content.split("**");
        QStringList contentActions = content2[1].split("||");

        if (contentActions.contains(action))
            result.append(content2[0]);
    }
    return result;
}




QStringList MainForm::getListOfFiles(const QString& path, const QString& ext)
{
    QStringList result;

    QDir dir(path);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dir.setNameFilters(QStringList() << "*" + ext);

    foreach(QFileInfo fileInfo, dir.entryInfoList())
    {
        // open the ingredient file
        QFile file(fileInfo.absoluteFilePath());
        if (!file.open(QFile::ReadOnly))
            speedDialog("c", "Erreur", "Impossible d'accéder à l'ingrédient.");
        QString content = file.readAll();

        // split and get ingredient's name
        result.append(content.section("**", 0, 0));
        file.close();
    }
    return result;
}



void MainForm::closeAddRecipeDialog()
{
    if (ingredients.size() > 0 || this->rNameInput->text().length() > 0){
        if (QMessageBox::question(this, "Perte d'information", "La recette en cours sera perdue.<br />Voulez-vous continuer ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
            ingredients.clear();
            this->addRecipeDialog->close();
        }
    } else
        this->addRecipeDialog->close();
}



void MainForm::chooseImageRecipe()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choisissez une image...", "./", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        this->imageRecipePath->setProperty("text", fileName);
        QPixmap recipePic = QPixmap(fileName).scaled(130, 123, Qt::KeepAspectRatio, Qt::FastTransformation);
        this->recipeImage->setPixmap(recipePic);
    }
}


void MainForm::closeAssocIngrRecipeDialog()
{
    this->ingrToRecipeDialog->close();
}



QFrame* MainForm::traceLine()
{
    QFrame *line = new QFrame(); // horizontal bar
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);//end

    return line;
}





void MainForm::openAddNewIngredient()
{
    // open a new dialogbox
    addIngredientDialog = new QDialog(this);
    addIngredientDialog->setModal(true);
    addIngredientDialog->setFixedSize(375, 415); // resize
    addIngredientDialogLayout = new QVBoxLayout; // main vertical layout

    // paint the logo of dialog
    pictureIngredient = new QLabel;
    pictureIngredient->setPixmap(QPixmap("pictures/ingredients.png"));
    addIngredientDialogLayout->addWidget(pictureIngredient);
    pictureIngredient->setAlignment(Qt::AlignTop);

    // groupbox adding ingredient
    groupAddIngredient = new QGroupBox(" Ajouter un ingrédient ", this);
    addIngredientDialogLayout->addWidget(groupAddIngredient);

    // main form
    addIngredientLayout = new QGridLayout;
    ingredientNameEdit = new QLineEdit;
    ingredientNameLabel = new QLabel("Nom de l'ingrédient : ");
    ingredientPerishableLabel = new QLabel("Ingrédient périssable ");
    ingredientNoUnitLabel = new QLabel("Unité de mesure nécessaire ");
    chooseUnit = new QLabel("Unités disponibles");
    ingrUnit = new QLabel("Unités de l'ingrédient");

    manageUnities = new QPushButton(" Nouvelle unité... ");
    addToIngr = new QPushButton("Ajouter >");
    removeToIngr = new QPushButton("< Retirer");

    ingredientPerishableBox = new QCheckBox;
    needUnit = new QCheckBox;
    unitiesListBox = new QListWidget;
    unitiesComboBox = new QComboBox;
    groupUnities = new QGroupBox;

    QFrame *line = traceLine();

    addIngredientLayout->addWidget(ingredientNameLabel, 0, 0);
    addIngredientLayout->addWidget(ingredientNameEdit, 0, 1);
    addIngredientLayout->addWidget(ingredientPerishableLabel, 1, 0);
    addIngredientLayout->addWidget(ingredientPerishableBox, 1, 1);
    addIngredientLayout->addWidget(line, 3, 0, 1, 2);
    addIngredientLayout->addWidget(ingredientNoUnitLabel, 5, 0);
    addIngredientLayout->addWidget(needUnit, 5, 1);

    // ingredients units
    unitLayout = new QGridLayout;
    unitLayout->addWidget(chooseUnit, 0, 0);
    unitLayout->addWidget(unitiesComboBox, 1, 0);
    unitLayout->addWidget(addToIngr, 2, 0);
    unitLayout->addWidget(removeToIngr, 3, 0);
    unitLayout->addWidget(ingrUnit, 0, 1, 1, 2, Qt::AlignCenter);
    unitLayout->addWidget(unitiesListBox, 1, 1, 3, 2);
    unitLayout->addWidget(manageUnities, 4, 2, 1, 1, Qt::AlignRight);
    removeToIngr->setDisabled(true);

    // add unit layout to main form layout
    groupUnities->setLayout(unitLayout);
    addIngredientLayout->addWidget(groupUnities, 6, 0, 1, 2);

    // add form layout to the groupbox
    groupAddIngredient->setLayout(addIngredientLayout);

    // draw cancel and submit buttons
    addIngredientBottomLayout = new QHBoxLayout;
    addIngredientCancel = new QPushButton("Annuler");
    addIngredientSave = new QPushButton("Ajouter");
    addIngredientBottomLayout->addWidget(addIngredientCancel);
    addIngredientBottomLayout->addWidget(addIngredientSave);
    addIngredientBottomLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);

    // fill combobox for unities
    unitiesComboBox->addItems(getListOfDelimiters());
    if (unitiesComboBox->count() == 0){
        addToIngr->setDisabled(true);
        unitiesComboBox->setDisabled(true);
    }

    addIngredientDialogLayout->addLayout(addIngredientBottomLayout);
    addIngredientDialog->setLayout(addIngredientDialogLayout);

    // display the dialogbox and disabled units groupbox
    checkBoxNoUnitIngredient(false);
    addIngredientDialog->show();

    connect(needUnit, SIGNAL(clicked()), this, SLOT(checkBoxNoUnitIngredient()));
    connect(addToIngr, SIGNAL(clicked()), this, SLOT(addUnit())); // add to unities for this ingredient
    connect(removeToIngr, SIGNAL(clicked()), this, SLOT(removeUnit()));
    connect(manageUnities, SIGNAL(clicked()), this, SLOT(openManageUnities()));
    connect(addIngredientCancel, SIGNAL(clicked()), this, SLOT(closeAddIngredientDialog())); // cancel action
    connect(addIngredientSave, SIGNAL(clicked()), this, SLOT(addNewIngredient())); // save ingredient action
}




void MainForm::openManageUnities()
{
    // open a new dialogbox
    manageUnitiesDialog = new QDialog(this);
    manageUnitiesDialog->setModal(true);
    manageUnitiesDialog->setFixedSize(315, 290); // resize
    unitiesVLayout = new QVBoxLayout;
    manageUnitiesDialog->setLayout(unitiesVLayout);

    logoUnities = new QLabel;
    logoUnities->setPixmap(QPixmap("pictures/unities.png"));
    unitiesVLayout->addWidget(logoUnities, 1, Qt::AlignCenter | Qt::AlignTop);

    unitiesMainBox = new QGroupBox(" Gestion des unités ");
    unitiesMainGridLayout = new QGridLayout;
    unitiesMainBox->setLayout(unitiesMainGridLayout);
    unitiesVLayout->addWidget(unitiesMainBox);

    newUnitLabel = new QLabel("Nouvelle unité : ");
    newUnitInput = new QLineEdit;
    addNewUnit = new QPushButton("Créer");

    unitiesMainGridLayout->addWidget(newUnitLabel, 0, 0);
    unitiesMainGridLayout->addWidget(newUnitInput, 0, 1);
    unitiesMainGridLayout->addWidget(addNewUnit, 0, 2);

    unitiesAvailablesBox = new QGroupBox(" Unités disponibles ");
    unitiesAvailablesLayout = new QHBoxLayout;
    unitiesAvailablesBox->setLayout(unitiesAvailablesLayout);
    unitiesMainGridLayout->addWidget(unitiesAvailablesBox, 1, 0, 1, 3);

    availableUnitiesList = new QComboBox;
    availableUnitiesList->addItems(getListOfDelimiters()); // fill the combobox with current unities

    // if there is no unities right now
    if (availableUnitiesList->count() == 0)
        unitiesAvailablesBox->setDisabled(true);

    removeOldUnit = new QPushButton("Supprimer");
    removeAllUnities = new QPushButton("Suppr. toutes");
    unitiesAvailablesLayout->addWidget(availableUnitiesList);
    unitiesAvailablesLayout->addWidget(removeOldUnit);
    unitiesAvailablesLayout->addWidget(removeAllUnities);

    unitiesBottomLayout = new QHBoxLayout;
    unitiesVLayout->addLayout(unitiesBottomLayout);
    unitiesCancel = new QPushButton("Annuler");
    unitiesBottomLayout->addWidget(unitiesCancel);
    unitiesBottomLayout->setAlignment(Qt::AlignRight);

    manageUnitiesDialog->show();

    connect(unitiesCancel, SIGNAL(clicked()), this, SLOT(closeManageUnitiesDialog()));
    connect(removeOldUnit, SIGNAL(clicked()), this, SLOT(removeOldUnitMethod()));
    connect(removeAllUnities, SIGNAL(clicked()), this, SLOT(removeAllUnitiesMethod()));
    connect(addNewUnit, SIGNAL(clicked()), this, SLOT(addNewUnitMethod()));
}




void MainForm::openAddMaterial()
{
    // open a new dialogbox
    addMaterialDialog = new QDialog(this);
    addMaterialDialog->setModal(true);
    addMaterialDialog->setFixedSize(360, 450); // resize
    materialVLayout = new QVBoxLayout; // main vertical layout
    addMaterialDialog->setLayout(materialVLayout);

    logoMaterial = new QLabel;
    logoMaterial->setPixmap(QPixmap("pictures/material.png"));
    materialVLayout->addWidget(logoMaterial, 1, Qt::AlignCenter | Qt::AlignTop);

    materialMainBox = new QGroupBox(" Ajouter du matériel ");
    materialVLayout->addWidget(materialMainBox, 1, Qt::AlignTop);
    materialMainBoxGrid = new QGridLayout;
    materialMainBox->setLayout(materialMainBoxGrid);

    materialType = new QLabel("Type de materiel :");
    cutleriesRadio = new QRadioButton("Couvert / Couteau");
    containersRadio = new QRadioButton("Contenant");
    toolsRadio = new QRadioButton("Appareil");
    cutleriesRadio->setChecked(true); // default checked cutleries radiobutton

    materialMainBoxGrid->addWidget(materialType, 0, 0);
    materialMainBoxGrid->addWidget(cutleriesRadio, 0, 1);
    materialMainBoxGrid->addWidget(containersRadio, 1, 1);
    materialMainBoxGrid->addWidget(toolsRadio, 2, 1);

    materialNameLabel = new QLabel("Nom de l'outil :");
    materialNameInput = new QLineEdit;

    materialMainBoxGrid->addWidget(materialNameLabel, 3, 0);
    materialMainBoxGrid->addWidget(materialNameInput, 3, 1);


    // actions management
    availableActionsLabel = new QLabel("Actions disponibles");
    associatedActionsLabel = new QLabel("Actions associées à ce matériel");

    addActionButton = new QPushButton(" Gérer les actions et les associations... ");
    addToMaterial = new QPushButton("Ajouter >");
    removeToMaterial = new QPushButton("< Retirer");

    actionsListBox = new QListWidget;

    actionsComboBox = new QComboBox;
    actionsComboBox->addItems(getListOfActionsMaterial()); // fill available actions
    actionsComboBox->setEditable(true);

    if (actionsComboBox->count() == 0){
        actionsComboBox->setDisabled(true);
        addToMaterial->setDisabled(true);
    }

    groupAction = new QGroupBox;

    // actions
    actionsLayout = new QGridLayout;
    actionsLayout->addWidget(availableActionsLabel, 0, 0);
    actionsLayout->addWidget(actionsComboBox, 1, 0);
    actionsLayout->addWidget(addToMaterial, 2, 0);
    actionsLayout->addWidget(removeToMaterial, 3, 0);
    actionsLayout->addWidget(associatedActionsLabel, 0, 1, 1, 2, Qt::AlignCenter);
    actionsLayout->addWidget(actionsListBox, 1, 1, 3, 2);
    actionsLayout->addWidget(addActionButton, 4, 2, 1, 1, Qt::AlignRight);
    removeToMaterial->setDisabled(true);

    // add unit layout to main form layout
    groupAction->setLayout(actionsLayout);
    materialMainBoxGrid->addWidget(groupAction, 4, 0, 1, 2);

    materialBottomLayout = new QHBoxLayout;

    addMaterialCancel = new QPushButton("Annuler");
    addMaterialValidate = new QPushButton("Ajouter");
    materialBottomLayout->addWidget(addMaterialCancel);
    materialBottomLayout->addWidget(addMaterialValidate);
    materialVLayout->addLayout(materialBottomLayout);
    materialBottomLayout->setAlignment(Qt::AlignRight);

    addMaterialDialog->show();

    connect(addActionButton, SIGNAL(clicked()), this, SLOT(openManageActions()));
    connect(removeToMaterial, SIGNAL(clicked()), this, SLOT(removeActionMaterial()));
    connect(addToMaterial, SIGNAL(clicked()), this, SLOT(addActionMaterial()));
    connect(addMaterialCancel, SIGNAL(clicked()), this, SLOT(closeAddMaterialDialog()));
    connect(addMaterialValidate, SIGNAL(clicked()), this, SLOT(addMaterialMethod()));
}




void MainForm::addMaterialMethod()
{
    if (this->materialNameInput->text() == QString("")){
        speedDialog("w", "Impossible", "Vous devez renseigner un nom de matériel.");
        return;
    }

    if (this->actionsListBox->count() == 0){
        speedDialog("w", "Impossible", "Un matériel doit être associé à au moins une action.");
        return;
    }

    QFile file("res/material/" + this->materialNameInput->text() + ".mat");
    if (!file.open(QFile::WriteOnly))
        speedDialog("c", "Erreur", "Impossible de créer le fichier du matériel.");

        // now, write new material
    QTextStream out(&file);
    out << this->materialNameInput->text() + "**" + this->actionsListBox->item(0)->text();

    if (this->actionsListBox->count() > 1) {
        for (int i = 1; i < this->actionsListBox->count(); i++)
            out << "||" + this->actionsListBox->item(i)->text();
    }

    string type = "L'appareil ";
    if (this->cutleriesRadio->isChecked()) {
        out << "**1";
        type = "Le couvert ";
    } else if (this->containersRadio->isChecked()) {
        out << "**2";
        type = "Le contenant ";
    } else
        out << "**3";

    file.close();

    speedDialog("i", "Ajout effectué", type + "\"<strong>" + this->materialNameInput->text().toStdString() + "</strong>\" a bien été ajouté.");
    closeAddMaterialDialog();
    openAddMaterial();
}




void MainForm::openManageActions()
{
    // open a new dialogbox
    manageActionsDialog = new QDialog(this);
    manageActionsDialog->setModal(true);
    manageActionsDialog->setFixedSize(360, 450); // resize
    actionsVLayout = new QVBoxLayout;
    manageActionsDialog->setLayout(actionsVLayout);

    logoActions = new QLabel;
    logoActions->setPixmap(QPixmap("pictures/actions.png"));
    actionsVLayout->addWidget(logoActions, 1, Qt::AlignCenter | Qt::AlignTop);

    actionsGlobalBox = new QGroupBox;
    actionsVLayout->addWidget(actionsGlobalBox);

    actionsVLayout2 = new QVBoxLayout;
    actionsGlobalBox->setLayout(actionsVLayout2);

    materialListBox = new QComboBox;
    selectMaterial = new QLabel("Selectionner un matériel :");
    // fill material combobox
    materialListBox->addItems(getListOfFiles("res/material", ".mat"));
    actionsHLayout = new QHBoxLayout;
    actionsVLayout2->addLayout(actionsHLayout);
    actionsHLayout->addWidget(selectMaterial);
    actionsHLayout->addWidget(materialListBox);

    actionsMainBox = new QGroupBox(" Ajout / Suppression d'actions ");

    actionsMainGridLayout = new QGridLayout;
    actionsMainBox->setLayout(actionsMainGridLayout);
    actionsVLayout2->addWidget(actionsMainBox);

// actions management
    availableActionsLabel2 = new QLabel("Actions disponibles");
    associatedActionsLabel2 = new QLabel("Actions pour le " + materialListBox->currentText());

    addActionButton2 = new QPushButton(" Appliquer ");
    addToMaterial2 = new QPushButton("Ajouter >");
    removeToMaterial2 = new QPushButton("< Retirer");

    actionsListBox2 = new QListWidget;
    actionsComboBox2 = new QComboBox;

    if (materialListBox->count() == 0)
        actionsMainBox->setDisabled(true);
    else{
        QStringList currentActions = getActionsFromMaterial(materialListBox->currentText());
        QStringList actionsList = getListWithoutDouble(getListOfActionsMaterial(), currentActions);
        actionsComboBox2->addItems(actionsList); // fill available actions
        actionsListBox2->addItems(currentActions); // fill the listview of current actions assigned to the current material

        if (actionsListBox2->count() == 0)
            removeToMaterial2->setDisabled(true);
    }

    if (actionsComboBox2->count() == 0){
        actionsComboBox2->setDisabled(true);
        addToMaterial2->setDisabled(true);
    }

    actionsMainGridLayout->addWidget(availableActionsLabel2, 1, 0);
    actionsMainGridLayout->addWidget(actionsComboBox2, 2, 0);
    actionsMainGridLayout->addWidget(addToMaterial2, 3, 0);
    actionsMainGridLayout->addWidget(removeToMaterial2, 4, 0);
    actionsMainGridLayout->addWidget(associatedActionsLabel2, 1, 1, 1, 2, Qt::AlignCenter);
    actionsMainGridLayout->addWidget(actionsListBox2, 2, 1, 3, 2);
    actionsMainGridLayout->addWidget(addActionButton2, 5, 2, 1, 1, Qt::AlignRight);

    newActionBox = new QGroupBox(" Ajouter une action ");
    addActionGrid = new QGridLayout;
    newActionBox->setLayout(addActionGrid);
    actionsVLayout2->addWidget(newActionBox);
    addActionLabel = new QLabel("Nom de l'action :");
    addNewActionButton = new QPushButton("Ajouter");
    newActionInput = new QLineEdit;

    addActionGrid->addWidget(addActionLabel, 0, 0);
    addActionGrid->addWidget(newActionInput, 0, 1);
    addActionGrid->addWidget(addNewActionButton, 0, 2);

    manageActionsCancel = new QPushButton("Annuler");
    actionsVLayout->addWidget(manageActionsCancel, 1, Qt::AlignRight);

    manageActionsDialog->show();

    connect(addToMaterial2, SIGNAL(clicked()), this, SLOT(addActionMaterial2()));
    connect(removeToMaterial2, SIGNAL(clicked()), this, SLOT(removeActionMaterial2()));
    connect(manageActionsCancel, SIGNAL(clicked()), this, SLOT(closeManageActions()));
    connect(materialListBox, SIGNAL(activated( const QString& )), this, SLOT(getSelectedMaterial()));
    connect(addActionButton2, SIGNAL(clicked()), this, SLOT(applyManageActions()));
    connect(addNewActionButton, SIGNAL(clicked()), this, SLOT(addNewActionMethod()));
}





void MainForm::addNewActionMethod()
{
    if (this->newActionInput->text() != QString("")){ // control

        QFile file("res/material/" + this->materialListBox->currentText() + ".mat");
        if (!file.open(QFile::ReadWrite))
            speedDialog("c", "Erreur", "Impossible d'accéder au materiel.");

        QString content = file.readAll();

        // first, we have to save the type of material (3th arg)

        QString materialType;
        QString actions;
        QString name;

        try
        {
            QStringList temp = content.split("**");
            materialType = temp[2];
            actions = temp[1];
            name = temp[0];
        }
        catch (const string& e)
        {
            qDebug() << QString::fromStdString(e);
        }

        file.close();
        if (!file.open(QFile::WriteOnly))
            speedDialog("c", "Erreur", "Impossible d'accéder au materiel.");

        // now, generate new list of action
        QTextStream out(&file);

        out << name + "**" + actions + "||" + this->newActionInput->text() + "**" + materialType;

        speedDialog("i", "Ajout effectué", "L'action \"<strong>" + this->newActionInput->text().toStdString() + "\"</strong> a bien été associée au matériel \"" + name.toStdString() + "\"");
        file.close();

        // update last window if need
        if (this->actionsComboBox){
            this->actionsComboBox->clear();
            this->actionsComboBox->addItems(getListOfActionsMaterial());
        }

        closeManageActions();
        openManageActions();
    }
}





void MainForm::applyManageActions()
{
    if (this->actionsListBox2->count() == 0){
        speedDialog("w", "Impossible", "Un matériel doit obligatoirement être associé à une action !");
        return;
    }

    QFile file("res/material/" + this->materialListBox->currentText() + ".mat");
    if (!file.open(QFile::ReadWrite))
        speedDialog("c", "Erreur", "Impossible d'accéder au materiel.");

    QString content = file.readAll();

    // first, we have to save the type of material (3th arg)
    QString materialType;
    try
    {
        QStringList temp = content.split("**");
        materialType = temp[2];
    }
    catch (const string& e)
    {
        qDebug() << QString::fromStdString(e);
    }

    file.close();
    if (!file.open(QFile::WriteOnly))
        speedDialog("c", "Erreur", "Impossible d'accéder au materiel.");

    // now, generate new list of action
    QTextStream out(&file);

    out << this->materialListBox->currentText() + "**" + this->actionsListBox2->item(0)->text();

    for (int i = 1; i < this->actionsListBox2->count(); i++)
        out << "||" + this->actionsListBox2->item(i)->text();

    out << "**" + materialType;

    file.close();

    // update last window if need
    if (this->actionsComboBox){
        this->actionsComboBox->clear();
        this->actionsComboBox->addItems(getListOfActionsMaterial());
    }

    closeManageActions();
    openManageActions();
}





QStringList MainForm::getListWithoutDouble(const QStringList& baseList, const QStringList& itemsToAvoid)
{
    QStringList result;
    for (int i = 0; i < baseList.length(); i++){
        if (!itemsToAvoid.contains(baseList[i], Qt::CaseInsensitive))
            result << baseList[i];
    }
    return result;
}



void MainForm::closeManageActions()
{
    this->manageActionsDialog->close();
}



void MainForm::getSelectedMaterial()
{
    this->associatedActionsLabel2->setProperty("text", "Actions pour le " + this->materialListBox->currentText());

    // truncate listbox
    this->actionsListBox2->clear();

    // truncate combobox
    this->actionsComboBox2->clear();

    QStringList currentActions = getActionsFromMaterial(this->materialListBox->currentText());
    QStringList actionsList = getListWithoutDouble(getListOfActionsMaterial(), currentActions);
    this->actionsComboBox2->addItems(actionsList); // fill available actions
    this->actionsListBox2->addItems(currentActions);

    if (this->actionsComboBox2->count() > 0){
        this->addToMaterial2->setDisabled(false);
        this->actionsComboBox2->setDisabled(false);
    }
    else {
        this->addToMaterial2->setDisabled(true);
        this->actionsComboBox2->setDisabled(true);
    }

    if (this->actionsListBox2->count() > 0)
        this->removeToMaterial2->setDisabled(false);
    else
        this->removeToMaterial2->setDisabled(true);
}




void MainForm::addActionMaterial2()
{
    toggleActionToMaterial2(1);
}


void MainForm::removeActionMaterial2()
{
    toggleActionToMaterial2(-1);
}


void MainForm::toggleActionToMaterial2(short actionKey)
{
    // adding into ListWidget
   if (actionKey == 1) {
       if (this->actionsComboBox2->count() > 0){
            this->actionsListBox2->addItem(this->actionsComboBox2->currentText());
            this->actionsComboBox2->removeItem(this->actionsComboBox2->currentIndex());
        }
   }
   // removing from ListWidget
   else {
       if (!this->actionsListBox2->currentItem())
            return;

       if (this->actionsListBox2->count() > 0){
            this->actionsComboBox2->addItem(this->actionsListBox2->currentItem()->text().toAscii().data());
            delete this->actionsListBox2->currentItem();
       }
   }

   if (this->actionsListBox2->count() == 0)
        this->removeToMaterial2->setDisabled(true);
    else
        this->removeToMaterial2->setDisabled(false);

    if (this->actionsComboBox2->count() == 0){
        this->addToMaterial2->setDisabled(true);
        this->actionsComboBox2->setDisabled(true);
    }
    else {
        this->addToMaterial2->setDisabled(false);
        this->actionsComboBox2->setDisabled(false);
    }
}





QStringList MainForm::getListOfActionsMaterial(const QString& path, const QString& ext)
{
    QStringList result;

    QDir dir(path);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dir.setNameFilters(QStringList() << "*" + ext);

    foreach(QFileInfo fileInfo, dir.entryInfoList())
    {
        // open the current material file
        QFile file(fileInfo.absoluteFilePath());
        if (!file.open(QFile::ReadOnly))
            speedDialog("c", "Erreur", "Impossible d'accéder au materiel.");
        QString content = file.readAll();

        // split and get ingredient's name
        QStringList temp = content.split("**");
        result.append(temp[1].split("||"));
        file.close();
    }
    return result;
}




void MainForm::addActionMaterial()
{
    toggleActionToMaterial(1);
}


void MainForm::removeActionMaterial()
{
    toggleActionToMaterial(-1);
}


void MainForm::toggleActionToMaterial(short actionKey)
{
    // adding into ListWidget
   if (actionKey == 1) {
       if (this->actionsComboBox->count() > 0){
            this->actionsListBox->addItem(this->actionsComboBox->currentText());
            this->actionsComboBox->removeItem(this->actionsComboBox->currentIndex());
        }
   }
   // removing from ListWidget
   else {
       if (!this->actionsListBox->currentItem())
            return;

       if (this->actionsListBox->count() > 0){
            this->actionsComboBox->addItem(this->actionsListBox->currentItem()->text().toAscii().data());
            delete this->actionsListBox->currentItem();
       }
   }

   if (this->actionsListBox->count() == 0)
        this->removeToMaterial->setDisabled(true);
    else
        this->removeToMaterial->setDisabled(false);

    if (this->actionsComboBox->count() == 0){
        this->addToMaterial->setDisabled(true);
        this->actionsComboBox->setDisabled(true);
    }
    else {
        this->addToMaterial->setDisabled(false);
        this->actionsComboBox->setDisabled(false);
    }
}




void MainForm::closeAddMaterialDialog()
{
    this->addMaterialDialog->close();
}



void MainForm::removeAllUnitiesMethod()
{
    if (QMessageBox::question(this, "Perte d'information", "Toutes les unités de mesure seront supprimées.<br />Voulez-vous continuer ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        return;

    QFile file("res/unities/unities.mtc");
    if (!file.open(QFile::WriteOnly)) {
        speedDialog("c", "Erreur", "Il y a eu une erreur dans l'ouverture du fichier des unités...");
        return;
    }
    QTextStream out(&file);

    // write  nothing to delete unities
    out << "";
    file.close();

    // update the combobox in add ingredient form
    if (this->unitiesComboBox){
        this->unitiesComboBox->clear();
        this->unitiesComboBox->setDisabled(true);
        this->addToIngr->setDisabled(true);
    }

    closeManageUnitiesDialog();
    openManageUnities();
}




void MainForm::removeOldUnitMethod()
{
    QStringList unitList = getListOfDelimiters();
    bool isPresent = false;

    for (int i = 0; i < unitList.length(); i++) {
        if (unitList.at(i) == QString(this->availableUnitiesList->currentText())) {
            unitList.removeAt(i);
            isPresent = true;
        }
    }

    if (!isPresent)
        return;

    QFile file("res/unities/unities.mtc");
    if (!file.open(QFile::WriteOnly)) {
        speedDialog("c", "Erreur", "Il y a eu une erreur dans l'ouverture du fichier des unités...");
        return;
    }
    QTextStream out(&file);

    // write all now
    if (unitList.length() > 0) {
        out << unitList[0];
        for (int i = 1; i < unitList.length(); i++)
            out << endl << unitList[i];
    }

    file.close();

    // update the combobox in add ingredient form
    if (this->unitiesComboBox){
        this->unitiesComboBox->clear();
        this->unitiesComboBox->addItems(unitList);

        if (unitList.length() == 0){
            this->unitiesComboBox->setDisabled(true);
            this->addToIngr->setDisabled(true);
        } else {
            this->unitiesComboBox->setDisabled(false);
            this->addToIngr->setDisabled(false);
        }
    }

    closeManageUnitiesDialog();
    openManageUnities();
}



void MainForm::addNewUnitMethod()
{
    // no unit name => impossible
    if (this->newUnitInput->text() == QString("")) {
        speedDialog("w", "Création impossible", "La nouvelle unité doit porter un nom !");
        return;
    }

    QStringList unitList = getListOfDelimiters();
    for (int i = 0; i < unitList.length(); i++) {
        if (unitList[i] == this->newUnitInput->text()) {
            speedDialog("w", "Création impossible", "L'unité à créer existe déjà !");
            this->newUnitInput->setProperty("text", "");
            this->newUnitInput->setFocus();
            return;
        }
    }

    unitList.append(this->newUnitInput->text()); // add unit at the end of unities list

    // prepare for writting
    QFile file("res/unities/unities.mtc");
    if (!file.open(QFile::WriteOnly)) {
        speedDialog("c", "Erreur", "Il y a eu une erreur dans l'ouverture du fichier des unités...");
        return;
    }
    QTextStream out(&file);

    // write each old and new unit
    if (unitList.length() > 0) {
    out << unitList[0];
        for (int i = 1; i < unitList.length(); i++)
            out << endl << unitList[i];
    }

    speedDialog("i", "Création réussie", "L'unité \"<strong>" + this->newUnitInput->text().toStdString() + "</strong>\" a été créée !");
    file.close();

    // update the combobox in add ingredient form
    if (this->unitiesComboBox){
        this->unitiesComboBox->addItem(this->newUnitInput->text());
        this->unitiesComboBox->setDisabled(false);
        this->addToIngr->setDisabled(false);
    }

    closeManageUnitiesDialog();
    openManageUnities();
}




void MainForm::closeManageUnitiesDialog()
{
    this->manageUnitiesDialog->close();
}



void MainForm::addUnit()
{
    toggleUnitToIngredient(1);
}


void MainForm::removeUnit()
{
    toggleUnitToIngredient(-1);
}


void MainForm::toggleUnitToIngredient(short actionKey)
{
    // adding into ListWidget
   if (actionKey == 1) {
       if (this->unitiesComboBox->count() > 0){
            this->unitiesListBox->addItem(this->unitiesComboBox->currentText());
            this->unitiesComboBox->removeItem(this->unitiesComboBox->currentIndex());
        }
   }
   // removing from ListWidget
   else {
       if (!this->unitiesListBox->currentItem())
            return;

       if (this->unitiesListBox->count() > 0){
            this->unitiesComboBox->addItem(this->unitiesListBox->currentItem()->text().toAscii().data());
            delete this->unitiesListBox->currentItem();
       }
   }

   if (this->unitiesListBox->count() == 0)
        this->removeToIngr->setDisabled(true);
    else
        this->removeToIngr->setDisabled(false);

    if (this->unitiesComboBox->count() == 0){
        this->addToIngr->setDisabled(true);
        this->unitiesComboBox->setDisabled(true);
    }
    else {
        this->addToIngr->setDisabled(false);
        this->unitiesComboBox->setDisabled(false);
    }
}




void MainForm::checkBoxNoUnitIngredient(bool manualCommand)
{
    if (this->needUnit->isChecked() && manualCommand){ // enabled
        groupUnities->setDisabled(false);
        needUnit->setChecked(true);
    }
    else {// disabled
        groupUnities->setDisabled(true);
        needUnit->setChecked(false);
    }
}




QStringList MainForm::getListOfDelimiters(const QString& path)
{
    QStringList result;
    QFile file(path);

    if (!file.open(QFile::ReadOnly))
        speedDialog("c", "Erreur", "Impossible au fichier unités de mesure.");

    QTextStream in(&file);

    while(!in.atEnd())
        result.append(in.readLine());

    file.close();
    return result;
}




void MainForm::addNewIngredient()
{
    // make controls
    if (this->ingredientNameEdit->text() == "")
        speedDialog("w", "Erreur", "L'ingrédient ne porte pas de nom !");

    // a unity is required but no unit has been choosed
    else if (this->needUnit->isChecked() && this->unitiesListBox->count() == 0)
        speedDialog("w", "Erreur", "Vous devez choisir au minimum une unité<br />de mesure pour cet ingrédient !");

    // all is OK for treatment
    else {
        // preparing the file writter
        QFile file("res/ingredients/" + this->ingredientNameEdit->text() + ".ingr");
        if (!file.open(QFile::WriteOnly)) {
            speedDialog("c", "Erreur", "Il y a eu une erreur dans l'ouverture du fichier...");
            return;
        }
        QTextStream out(&file);

        QString unities;
        if (this->needUnit->isChecked())
        {
            // detect checked unities
            QStringList unitiesList;
            for (int i = 0; i < this->unitiesListBox->count(); i++)
                unitiesList.append(this->unitiesListBox->item(i)->text().toAscii().data());

            unities = unitiesList[0];
            unitiesList.pop_front();
            foreach (QString u, unitiesList)
                unities += "||" + u;
        }
        else // no need of unit (eggs, fruits...)
            unities = "-";

        // write into a new file
        out << this->ingredientNameEdit->text() << "**" << unities << "**" << (int)this->ingredientPerishableBox->isChecked();
        file.close();

        // show confirmation
        speedDialog("i", "Action effectuée", "L'ingrédient \"<strong>" + this->ingredientNameEdit->text().toStdString() + "</strong>\" a bien été ajouté !");

        // reset the form
        this->ingredientNameEdit->setProperty("text", "");
        this->ingredientPerishableBox->setChecked(false);
        closeAddIngredientDialog();
        openAddNewIngredient();
    }
}



void MainForm::openAbout()
{
    // open a new dialogbox
    aboutDialog = new QDialog(this);
    aboutDialog->setModal(true);
    aboutDialog->setFixedSize(350, 430); // resize

    aboutDialogLayout = new QVBoxLayout;
    aboutMainLayout = new QVBoxLayout; // main verticals layouts
    aboutBottomLayout = new QHBoxLayout;

    groupAboutText = new QGroupBox("A propos de Mastop Chef", this);
    aboutMainLayout->addWidget(groupAboutText);
    groupAboutText->setLayout(aboutDialogLayout);

    // paint the logo of dialog
    pictureAbout = new QLabel;
    pictureAbout->setPixmap(QPixmap("pictures/logo.png"));
    pictureAbout->setAlignment(Qt::AlignCenter);
    aboutDialogLayout->addWidget(pictureAbout);

    // text about
    aboutText = new QLabel("Programme C++ réalisé avec Qt4 par :<ul type=\"disc\"><li><b>DE BATZ Christophe</b></li><li><b>BERTRAND Benjamin</b></li></ul>Ce programme a été développé dans le cadre d'un TP de<br />programmation à l'EFREI Paris et est distribué sous<br />licence Creative Commons.<br /><br />Mastop Chef v1.0 - tous droits réservés");
    aboutDialogLayout->addWidget(aboutText);

    returnButton = new QPushButton("Retour");
    reportingButton = new QPushButton(" Rapport du projet ");
    aboutBottomLayout->addWidget(reportingButton);
    aboutBottomLayout->addWidget(returnButton);
    aboutBottomLayout->setAlignment(Qt::AlignRight);
    aboutMainLayout->addLayout(aboutBottomLayout);

    aboutDialog->setLayout(aboutMainLayout);
    aboutDialog->show();

    connect(returnButton, SIGNAL(clicked()), this, SLOT(closeAbout()));
    connect(reportingButton, SIGNAL(clicked()), this, SLOT(openReporting()));
}


// open the reporting at pdf format
void MainForm::openReporting()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile("Rapport_mastop_chef.pdf")))
        speedDialog("c", "Erreur", "Impossible d'ouvrir le fichier...");
}


// close about dialog
void MainForm::closeAbout()
{
    aboutDialog->close();
}



// close windows of adding ingredient
void MainForm::closeAddIngredientDialog()
{
    addIngredientDialog->close();
}



void MainForm::speedDialog(const string& dialogType, const string& title, const string& msg)
{
    if (dialogType == "w")
            QMessageBox::warning(this, QString::fromStdString(title), QString::fromStdString(msg));

    if (dialogType == "c")
            QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(msg));

    if (dialogType == "i")
            QMessageBox::information(this, QString::fromStdString(title), QString::fromStdString(msg));

    return;
}


/**
*  destructor
*
*   @param  void
*   @return void
*
*/
MainForm::~MainForm()
{
    delete this;
}
