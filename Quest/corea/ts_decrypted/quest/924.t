CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 924;
	title = 92402;

	CNtlTSGroup
	{
		gid = 0;

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
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 92408;
			gtype = 2;
			oklnk = 2;
			area = 92401;
			goal = 92404;
			sort = 92405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 92402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 92414;
			nextlnk = 101;
			rwdtbl = 92401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 92407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3142110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 40;
				minlvl = 32;
			}
			CDboTSCheckClrQst
			{
				and = "923;";
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
				conv = 92409;
				ctype = 1;
				idx = 3142110;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 92408;
				gtype = 2;
				area = 92401;
				goal = 92404;
				m0fz = "1397.000000";
				m0widx = 1;
				sort = 92405;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3744.000000";
				m0ttip = 92415;
				rwd = 100;
				taid = 1;
				title = 92402;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 7901100;
				cnt0 = 6;
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
				itype = 0;
			}
		}
	}
}

