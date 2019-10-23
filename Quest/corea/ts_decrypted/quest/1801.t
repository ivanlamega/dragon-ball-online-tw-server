CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1801;
	title = 180102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 180109;
				ctype = 1;
				idx = 5061108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 180108;
				gtype = 2;
				area = 180101;
				goal = 180104;
				m0fz = "1004.000000";
				m0widx = 1;
				sort = 180105;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3470.000000";
				m0ttip = 180115;
				rwd = 100;
				taid = 1;
				title = 180102;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 1087;
				cnt0 = 20;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
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
				eitype = 1;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 180114;
			nextlnk = 101;
			rwdtbl = 180101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061108;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 20;
				iidx = 1087;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 180108;
			gtype = 2;
			oklnk = 2;
			area = 180101;
			goal = 180104;
			sort = 180105;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 180102;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 180107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 40;
				minlvl = 32;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 1087;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 180107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

