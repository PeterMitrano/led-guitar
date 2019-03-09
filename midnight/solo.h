#include "util.h"
unsigned int const us_per_dt = 18750;
constexpr unsigned int const outline_events_size = 23;
OutlineEvent const outline_events[] = {
  OutlineEvent{0u, 32u, 61u},
  OutlineEvent{32u, 32u, 62u},
  OutlineEvent{64u, 32u, 63u},
  OutlineEvent{96u, 32u, 64u},
  OutlineEvent{128u, 32u, 61u},
  OutlineEvent{160u, 32u, 62u},
  OutlineEvent{192u, 32u, 63u},
  OutlineEvent{224u, 32u, 64u},
  OutlineEvent{256u, 32u, 65u},
  OutlineEvent{288u, 32u, 66u},
  OutlineEvent{320u, 32u, 67u},
  OutlineEvent{352u, 32u, 68u},
  OutlineEvent{384u, 32u, 65u},
  OutlineEvent{416u, 32u, 66u},
  OutlineEvent{448u, 32u, 67u},
  OutlineEvent{480u, 32u, 68u},
  OutlineEvent{512u, 96u, 69u},
  OutlineEvent{608u, 160u, 70u},
  OutlineEvent{768u, 32u, 72u},
  OutlineEvent{800u, 32u, 73u},
  OutlineEvent{832u, 32u, 74u},
  OutlineEvent{864u, 32u, 75u},
  OutlineEvent{896u, 384u, 76u},
};
constexpr unsigned int const fret_events_size = 48;
FretEvent const fret_events[] = {
  FretEvent{0u, 64u, 1u, 14u},
  FretEvent{64u, 40u, 1u, 12u},
  FretEvent{104u, 8u, 1u, 5u},
  FretEvent{112u, 16u, 1u, 7u},
  FretEvent{128u, 16u, 1u, 9u},
  FretEvent{144u, 16u, 1u, 12u},
  FretEvent{160u, 8u, 1u, 9u},
  FretEvent{168u, 8u, 1u, 7u},
  FretEvent{176u, 8u, 1u, 5u},
  FretEvent{184u, 24u, 1u, 5u},
  FretEvent{208u, 8u, 1u, 2u},
  FretEvent{216u, 8u, 1u, 0u},
  FretEvent{224u, 8u, 1u, 2u},
  FretEvent{232u, 24u, 1u, 5u},
  FretEvent{256u, 32u, 1u, 7u},
  FretEvent{288u, 16u, 1u, 5u},
  FretEvent{304u, 32u, 1u, 9u},
  FretEvent{336u, 16u, 1u, 5u},
  FretEvent{352u, 8u, 1u, 4u},
  FretEvent{360u, 24u, 1u, 5u},
  FretEvent{384u, 32u, 1u, 7u},
  FretEvent{416u, 16u, 1u, 5u},
  FretEvent{432u, 48u, 1u, 9u},
  FretEvent{480u, 16u, 1u, 7u},
  FretEvent{496u, 16u, 1u, 5u},
  FretEvent{512u, 96u, 1u, 21u},
  FretEvent{608u, 12u, 1u, 17u},
  FretEvent{620u, 10u, 1u, 16u},
  FretEvent{630u, 10u, 1u, 14u},
  FretEvent{640u, 24u, 1u, 12u},
  FretEvent{664u, 24u, 1u, 9u},
  FretEvent{688u, 8u, 1u, 7u},
  FretEvent{696u, 8u, 1u, 5u},
  FretEvent{704u, 16u, 1u, 9u},
  FretEvent{720u, 16u, 1u, 12u},
  FretEvent{736u, 8u, 1u, 9u},
  FretEvent{744u, 8u, 1u, 7u},
  FretEvent{752u, 16u, 1u, 5u},
  FretEvent{768u, 16u, 1u, 5u},
  FretEvent{784u, 8u, 1u, 2u},
  FretEvent{792u, 8u, 1u, 0u},
  FretEvent{800u, 8u, 1u, 2u},
  FretEvent{808u, 24u, 1u, 5u},
  FretEvent{832u, 16u, 1u, 7u},
  FretEvent{848u, 16u, 1u, 5u},
  FretEvent{864u, 8u, 1u, 4u},
  FretEvent{872u, 24u, 1u, 5u},
  FretEvent{896u, 384u, 4u, 0u},
};

