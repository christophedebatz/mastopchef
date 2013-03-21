#ifndef MAINFORM_H
#define MAINFORM_H

#include "Ingredient.h"
#include "Material.h"
#include "Machine.h"
#include "CookStep.h"
#include "Recipe.h"

#include <vector>
#include <list>
#include <QApplication>
#include <QtGui>


class MainForm : public QMainWindow
{
    Q_OBJECT

    public:
        MainForm();
        ~MainForm();
        void createMenu();
        void createTabs();
        void createTabsComponents();
        void createSearchQuarter();
        void speedDialog(const std::string& dialogType, const std::string& title, const std::string& msg);
        void refreshIngredientsList();
        void updateIngredientsAssociated();
        QStringList getListOfFiles(const QString& path = "res/ingredients", const QString& ext = ".ingr");
        QStringList getListOfDelimiters(const QString& path = "res/unities/unities.mtc");
        void toggleUnitToIngredient(short actionKey);
        QFrame* traceLine();
        void toggleActionToMaterial(short actionKey);
        QStringList getListOfActionsMaterial(const QString& path = "res/material", const QString& ext = ".mat");
        QStringList getActionsFromMaterial(const QString& materialName);
        QStringList getListWithoutDouble(const QStringList& baseList, const QStringList& itemsToAvoid);
        QStringList getMaterialFromAction(const QString& action);

    private slots:
        void closeAddIngredientDialog();
        void openAddNewIngredient();
        void openAddNewRecipe();
        void openAbout();
        void openReporting();
        void closeAbout();
        void chooseImageRecipe();
        void closeAddRecipeDialog();
        void openAssocIngrRecipeDialog();
        void addNewIngredient();
        void getUnitsFromIngredient(const QString& ingredientName);
        void closeAssocIngrRecipeDialog();
        void applyIngrRecipeAssoc();
        void removeIngr();
        void checkBoxNoUnitIngredient(bool manualCommand = true);
        void openAddCookStep();
        void addUnit();
        void removeUnit();
        void openManageUnities();
        void closeManageUnitiesDialog();
        void addNewUnitMethod();
        void removeOldUnitMethod();
        void removeAllUnitiesMethod();
        void openAddMaterial();
        void closeAddMaterialDialog();
        void removeActionMaterial();
        void addActionMaterial();
        void openManageActions();
        void getSelectedMaterial();
        void closeManageActions();
        void addActionMaterial2();
        void removeActionMaterial2();
        void toggleActionToMaterial2(short actionKey);
        void applyManageActions();
        void addNewActionMethod();
        void addMaterialMethod();
        void getMaterialFromActionRefresh();
        void closeAddStepDialog();
        void addCookStepMethod();
        void removeStepToRecipe();
        void submitRecipeMethod();
        void openRecipe();

    private:
        std::list<CookStep> cookSteps;
        std::vector<std::string> temporalyIngr;
        std::vector<Ingredient> ingredients;

        // main window
        QGridLayout *mainGridLayout, *generalGridLayout;
        QTabWidget *tabs;
        QWidget *centeredZone, *tabIngredients, *tabGeneral, *tabPreparation;
        QGroupBox *groupGeneral, *groupSearch;
        QLabel *logo, *imageRecipe, *recipeGeneral, *recipeIngr, *recipePrepare;
        QHBoxLayout *layoutGeneral, *layoutIngr, *layoutPrepare, *layoutSearch;

        // add ingredient dialogbox
        QGroupBox *groupAddIngredient, *groupUnities;
        QVBoxLayout *addIngredientDialogLayout;
        QHBoxLayout *addIngredientBottomLayout;
        QGridLayout *addIngredientLayout, *unitLayout;
        QDialog *addIngredientDialog;
        QLineEdit *ingredientNameEdit;
        QLabel *pictureIngredient, *ingredientPerishableLabel, *ingredientNameLabel, *ingredientNoUnitLabel, *chooseUnit, *ingrUnit;
        QCheckBox *ingredientPerishableBox, *needUnit;
        QComboBox *unitiesComboBox;
        QListWidget *unitiesListBox;
        QPushButton *addIngredientCancel, *addIngredientSave, *manageUnities, *addToIngr, *removeToIngr;

        // about dialogbox
        QDialog *aboutDialog;
        QLabel *pictureAbout, *aboutText;
        QGroupBox *groupAboutText;
        QPushButton *returnButton, *reportingButton;
        QHBoxLayout *aboutBottomLayout;
        QVBoxLayout *aboutDialogLayout, *aboutMainLayout;

        // addrecipe dialog
        QVBoxLayout *addRecipeDialogLayout;
        QHBoxLayout *addRecipeBottomLayout, *addRecipeMiddleLayout;
        QGridLayout *addRecipeIngredientLayout, *addRecipeProtocolLayout;
        QFormLayout *addRecipeLayout;
        QGroupBox *groupAddRecipe1, *groupAddRecipe2, *groupAddRecipe3;
        QDialog *addRecipeDialog;
        QLabel *pictureRecipe, *recipeImage, *imageRecipePath;
        QPushButton *addRecipeCancel, *setImageRecipe, *addIngredientToRecipe, *removeIngredientToRecipe, *addStep, *removeStep, *submitRecipe;
        QLineEdit *rNameInput;
        QSpinBox *rCapacityInput;
        QComboBox *rDifficultyInput;
        QListWidget *listIngredients, *listSteps;

        // add ingredient TO RECIPE mini dialog
        QDialog *ingrToRecipeDialog;
        QLabel *ingrNameLabel, *ingrQuantityLabel;
        QVBoxLayout *ingrToRecipeVLayout;
        QHBoxLayout *ingrToRecipeBottomLayout;
        QGridLayout *ingrToRecipeGridLayout;
        QGroupBox *ingrToRecipeBox;
        QDoubleSpinBox *ingrQuantity;
        QComboBox *ingrListName, *ingrListUnit;
        QPushButton *ingrToRecipeValidate, *ingrToRecipeCancel, *openAddIngredientDialog;

        // add step dialog
        QDialog *addStepDialog;
        QVBoxLayout *addStepVLayout;
        QHBoxLayout *addStepBottomLayout;
        QGridLayout *addSTepGridLayout;
        QGroupBox *addStepMainGroup;
        QPushButton *addStepCancel, *addStepValidate;
        QSpinBox *timeContent;
        QLabel *actionLabel, *materialLabel, *ingredientLabel, *mediumIngrLabel, *timeLabel;
        QComboBox *selectActionRecipe, *selectMaterialRecipe, *selectIngrRecipe, *selectMediumIngrRecipe;

        // manage unities
        QDialog *manageUnitiesDialog;
        QGroupBox *unitiesMainBox, *unitiesAvailablesBox;
        QLabel *newUnitLabel, *logoUnities;
        QPushButton *addNewUnit, *removeOldUnit, *removeAllUnities, *unitiesCancel;
        QLineEdit *newUnitInput;
        QVBoxLayout *unitiesVLayout;
        QGridLayout *unitiesMainGridLayout;
        QHBoxLayout *unitiesAvailablesLayout, *unitiesBottomLayout;
        QComboBox *availableUnitiesList;

        // material dialog
        QDialog *addMaterialDialog;
        QVBoxLayout *materialVLayout;
        QLabel *logoMaterial, *materialType, *materialNameLabel, *availableActionsLabel, *associatedActionsLabel;
        QGroupBox *materialMainBox, *groupAction;
        QGridLayout *materialMainBoxGrid, *actionsLayout;
        QFormLayout *materialSpecs;
        QRadioButton *cutleriesRadio, *containersRadio, *toolsRadio;
        QLineEdit *materialNameInput;
        QHBoxLayout *materialBottomLayout;
        QPushButton *addMaterialValidate, *addMaterialCancel, *addActionButton, *addToMaterial, *removeToMaterial;
        QListWidget *actionsListBox;
        QComboBox *actionsComboBox;

        //actions dialog
        QDialog *manageActionsDialog;
        QVBoxLayout *actionsVLayout, *actionsVLayout2;
        QHBoxLayout *actionsHLayout;
        QLabel *logoActions, *selectMaterial, *availableActionsLabel2, *associatedActionsLabel2, *addActionLabel;
        QGridLayout *actionsMainGridLayout, *addActionGrid;
        QGroupBox *actionsMainBox, *newActionBox, *actionsGlobalBox;
        QComboBox *materialListBox, *actionsComboBox2;
        QPushButton *addActionButton2, *addToMaterial2, *removeToMaterial2, *addNewActionButton, *manageActionsCancel;
        QLineEdit *newActionInput;
        QListWidget *actionsListBox2;
};


#endif
