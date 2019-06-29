
#ifndef SCANTAILOR_COLORSCHEME_H
#define SCANTAILOR_COLORSCHEME_H

#include <QColor>
#include <unordered_map>

class QStyle;
class QPalette;
class QString;

class ColorScheme {
 public:
  virtual ~ColorScheme() = default;

  virtual QStyle* getStyle() const = 0;

  virtual const QPalette* getPalette() const = 0;

  virtual const QString* getStyleSheet() const = 0;

  enum ColorParam {
    ThumbnailSequenceItemText,
    ThumbnailSequenceSelectedItemText,
    ThumbnailSequenceSelectedItemBackground,
    ThumbnailSequenceSelectionLeaderText,
    ThumbnailSequenceSelectionLeaderBackground,
    RelinkablePathVisualizationBorder,
    OpenNewProjectBorder,
    ProcessingIndicationHeadColor,
    ProcessingIndicationTail,
    ProcessingIndicationFade,
    StageListHead,
    StageListTail,
    FixDpiDialogErrorText
  };

  using ColorParams = std::unordered_map<ColorParam, QColor, std::hash<int>>;

  /**
   * List of colors for elements that don't support styling.
   *
   * @return the list of colors to override the default values by the color scheme
   */
  virtual const ColorParams* getColorParams() const = 0;
};

#endif  // SCANTAILOR_COLORSCHEME_H