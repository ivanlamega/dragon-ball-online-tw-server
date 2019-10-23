CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 897;
	title = 89702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 89709;
				ctype = 1;
				idx = 3031202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 89708;
				m1fx = "7475.549805";
				area = 89701;
				goal = 89704;
				m0fz = "-691.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 89716;
				sort = 89705;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-189.429993";
				grade = 132203;
				m0fx = "6741.000000";
				m0ttip = 89715;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 89702;
				gtype = 0;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 18;
				eitype = 0;
				idx0 = 8911100;
				cnt0 = 25;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 8911101;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 89707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 32;
				minlvl = 24;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 89708;
			gtype = 0;
			oklnk = 2;
			area = 89701;
			goal = 89704;
			sort = 89705;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 89702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 89714;
			nextlnk = 101;
			rwdtbl = 89701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031202;
			}
		}
	}
}

