#ifndef CCONSTANTS_HPP
#define CCONSTANTS_HPP

#include <QString>

class CConstant {
    public:
        static QString getSavedProjectsFolder() { return SAVED_PROJECTS_FOLDER; }
        static QString getProjectizerMainFolder() { return PROJECTIZER_MAIN_FOLDER; }
        static QString getTemplatesFolder() { return TEMPLATES_FOLDER; }
    private:
        const static QString SAVED_PROJECTS_FOLDER;
        const static QString PROJECTIZER_MAIN_FOLDER;
        const static QString TEMPLATES_FOLDER;
};

#endif // CCONSTANTS_HPP
