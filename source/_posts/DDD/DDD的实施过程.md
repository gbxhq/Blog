---
title: DDD 实施过程
date: 2020-01-19
categories: DDD
tags: [DDD]
---

# 战略设计阶段

战略阶段重要性不言而喻，但战略一旦定了不会经常变动。围绕整个产品的愿景、核心竞争力，回答要解决什么核心问题，用什么关键技术手段、配备多少人力、物力资源。

目标：战略设计阶段会完成：

1. 【划出第一重边界】针对产品愿景、业务要解决的问题域，规划核心域、通用域、支撑域，做合适的资源投入
2. 【划出第二重边界】基于分析阶段的领域提炼的成果，划分限界上下文（bounded context），确定限界上下文之间如何协作。
3. 【划出第三重边界】架构层面制定分层架构，隔离关注点，减少核心的领域层沉淀并稳定下来，尽量不会因为外界变化而发生大的变动

参与角色：各领域专家、架构师、管理团队

何时完成：一般在产品规划时开展，后续业务变化了继续在原先的基础上做战略调整。比如产品规划会、重大需求调整计划会

产出：1. 维护整个业务的限界上下文列表（包括中英文名称、职责范围、所属团队）

方法：没有固定的操作方法论，主要关注限界上下文职责完整合理、团队资源的匹配度（康威定律）。

所谓“领域专家”不是一个头衔，也不是对技能级别的要求，它指代“懂业务”的人。懂业务不仅指了解已有业务的流程、逻辑。最好要懂业务的价值，跟整个产品的价值定位，企业管理运营的契合度。领域专家可以是业务人员、PM、QA、RD等任何懂业务的人。

## **如何划分限界上下文？**

参考[DDD的架构](https://wiki2ku.baidu-int.com/pubapi/urlmap?id=1233474887)相关章节

# 模型分析阶段

分析阶段需要业务、产品、技术团队紧密合作，围绕特定的问题域，提炼出完整的领域概念，形成领域的通用语言，为后续跨团队协同战术动作奠定坚实基础。

目标：识别提炼出领域概念，它们大致的关系是什么？比如概念A必须依附B存在，先做C再做D，做完E步骤必须见到F等等。

参与角色：PM、领域专家、敏捷小组

何时完成：比如需求讨论&交接会

产出：1. 维护本限界上下文的通用语言表 2. 维护本限界上下文的领域模型分析图

方法：业界有很多领域模型建模方法：名词动词、四色建模、事件风暴等。简单领域采用名词动词法就够了，复杂领域利用其他方法。推荐采用四色建模方法。

## 如何高质量提炼领域知识之前提：需求质量

正如[DDD的入门](https://wiki2ku.baidu-int.com/pubapi/urlmap?id=1234179212)里说的，软件交付需要需求、技术、工程通力合作。需求和技术之间存在着一个明显的知识翻译流程，这个流程进行的质量往往决定了后续软件交付效果。这个翻译流程的质量影响面有方方面面，从市场/用户处如何提炼出有效需求，需求如何被抽象、裁剪，如何准确无误的解释给技术人员，技术人员如何在时效性、技术限制前提下再次抽象、裁剪后实现出来，每一次的信息传递熵增都会带来信息失真。

**编写好的用户故事（user story）**

用户故事应该只受到业务规则与业务流程变化的影响。只描述做什么，不关注怎么做。

- 不被UI操作流程捆绑，UI 操作不是业务行为 (用户想要的并不一定是真实需求)
- 不受技术实现干扰（技术现状只是眼前的苟且，真实需求才是诗和远方）
- 可验收，有交付标准（能衡量出效果的才是需求交付）

**澄清横向影响点（cross impact analysis）**

尽可能把横向影响点描述清楚，是否影响其他限界上下文，其他领域对象

## 如何高质量提炼领域知识：四色建模法

四色建模来源于Peter Coad的《彩色UML建模》，旨在把所有的模型对象抽象为四种，并在模型图里用四种不同的颜色标记出来。

### 四色是什么

1. 时刻-时间段原型（Moment-Interval Archetype，MI）
   这类对象用来记录某个时刻或某段时间内管理和运营数据，用粉色表示。比如订单系统里，订单就是典型的MI对象。
2. 参与方-地点-物品原型（Part-Place-Thing Archetype，PPT）
   业务流程中的参与者，可以是人、物、地点。用绿色表示。
3. 角色原型（Role Archetype）
   PPT对象在参与MI过程中，扮演的角色，用黄色表示。
4. 描述原型（Description Archetype）
   对PPT对象的更详细描述，用蓝色表示。

简单概括上面四种原型就是：具体一个什么人或物以某种角色在某个时刻或某段时间内在某个地点参与某个活动。 其中“具体、什么”就是描述原型，“人或物”、“某个地点”就是参与方-地点-物品原型，“角色”就是角色原型，而”某个时刻或某段时间内的某个活动记录"就是时刻-时间段原型。

### 如何运用四色建模进行领域分析

下面以电商系统下定单到订单配送完成举例，如何使用四色建模法来分析和提炼领域知识。

1. 确定系统的关键业务流程，分解出关键步骤。比如订单系统里的主要步骤是下订单→ 预扣库存 → 支付 → 打包 → 配送 → 完成

![img](http://rte.weiyun.baidu.com/api/imageDownloadAddress?attachId=0ea7c992a0684beaa4066791a3068006)

1. 
2. 这些关键步骤是否需要可追溯数据，缺失了是不是影响运营管理？需要可追溯的数据正是四色建模里的MI对象。如何识别MI对象？一看某个时间点或者时间段内业务动作是否会产生数据。二问如果没有这份数据会影响企业运营管理吗？比如下订单动作会产生订单数据，如果没有这些订单数据可追溯，后续的发货、支付基于什么来操作？客户要退订单怎么办？这就意味着订单数据必须作为MI对象存在系统里。

![img](http://rte.weiyun.baidu.com/api/imageDownloadAddress?attachId=d6a755a877f842f9a8443c0e96ef3d4a)

1. 
2. 识别出上述MI对象涉及到的参与方、地点、物品。比如上述订单对象，需要有下订单的人，订单里的商品，人和商品就是PPT对象。

![img](http://rte.weiyun.baidu.com/api/imageDownloadAddress?attachId=55cc2775f23f4da9b0fb6c7b33661244)

1. 
2. 根据上一步识别出来的MI对象和PPT对象，找出它们之间的关系，抽取出角色就是Role对象。比如订单和人之间的角色是客户，发货凭证和人之间是库存管理员，这是不同的角色。

![img](http://rte.weiyun.baidu.com/api/imageDownloadAddress?attachId=d43aaacfda624e40981d41721ae64dfd)

1. 
2. PPT对象往往还需要更多的补充信息，比如商品这个PPT对象可能还有供应商信息，上下架状态等，这些就是描述对象。

![img](http://rte.weiyun.baidu.com/api/imageDownloadAddress?attachId=2746c49542284489a8ef8a17f6fdc9cd)

1. 

小结：业务流程是为了满足业务系统的目标，业务系统的目标是要要支撑企业的日常运营、商业决策。而运营管理过程中每个动作都会留下痕迹，增删改查每个动作都会有相应的记录或凭证。根据运营流程中最关心的东西，留下重要的那些记录、凭证，往往这就是MI对象。一旦识别出了业务流程中的MI对象就形成了模型分析的主干，再围绕这个主干延伸出PPT对象，根据MI对象和PPT对象的关系识别出角色对象，最后识别出需要补充PPT对象的信息。四色建模流程紧密围绕业务目标展开，能充分提炼出一个完整的领域知识，最终得到有效的领域模型，是一种推荐的分析方法。

# 模型设计阶段

设计阶段是开发人员跟PM、领域专家弄清楚了领域知识之后，实际编码之前进行的领域元素设计，起着承上启下作用。设计阶段在DDD的战术层面非常重要，因为对编码影响很大，对下一次业务需求迭代效率奠定基础。

目标：基于领域模型分析图，进一步简化对象关系、明确对象职责、设计出以聚合为核心的设计模型，划出第四重边界

参与角色：领域专家、开发、测试

何时发生：迭代开发周期内

产出：1. 维护领域设计模型图 2. 可能会修改新增本限界上下文的通用语言表

方法：基于模型分析图，做实体+值对象设计，识别聚合，各自理清依赖关系。辅助以时序图可以识别出领域服务。如何设计具体的领域对象，详见[DDD的设计原则](https://wiki2ku.baidu-int.com/pubapi/urlmap?id=1233535631)。注意：得出设计模型图后需要返回需求，走查一遍具体需求，验证设计的领域模型是否合理。

### 领域模型设计图示例

![img](http://rte.weiyun.baidu.com/api/imageDownloadAddress?attachId=3cfe73cbdc2d497db86fd60317f2edfb)

### 配合时序图设计出领域服务

上面这种由类图表达的领域设计模型仍有不足之处，它没有明确每个对象的职责范围大小合适不合适，需不需要领域服务。如果针对某个具体场景画时序图的话可以更直观看出哪个对象承担的职责过多或者过少，从而更合理的确定出对象协作关系。

# 模型实现阶段

目标：基于模型设计图加以编码实现，并遵守架构规范和编码规范。

参与角色：开发、架构师

何时发生：迭代开发周期内

产出：项目代码，修正模型设计图

方法：基于DDD专门的二方库，满足[DDD的架构](https://wiki2ku.baidu-int.com/pubapi/urlmap?id=1233474887)，遵守相应编码规范。**特别要注意编码先后顺序的问题**，分析阶段的顺序是自上而下，从主干流程、业务场景到领域模型，编码阶段是自下而上。1. 先实现领域层的逻辑，不必考虑技术细节比如存储细节，rpc调用。2. 领域层完成后，实现应用层，编排业务场景。3.最后是接口层和基础设施层，接口层其实也是基础设施层的一部分。