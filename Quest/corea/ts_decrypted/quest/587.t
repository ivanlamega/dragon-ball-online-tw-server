CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 587;
	title = 58702;

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
				conv = 58709;
				ctype = 1;
				idx = 4141112;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 58708;
				gtype = 0;
				area = 58701;
				goal = 58704;
				m0fz = "-2160.000000";
				m0widx = 1;
				sort = 58705;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "7589.000000";
				m0ttip = 58715;
				rwd = 100;
				taid = 1;
				title = 58702;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 9612103;
				cnt0 = 12;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 58708;
			gtype = 0;
			oklnk = 2;
			area = 58701;
			goal = 58704;
			sort = 58705;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 58702;
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
			stdiag = 58707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4141112;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 26;
				minlvl = 18;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 58714;
			nextlnk = 101;
			rwdtbl = 58701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4141112;
			}
		}
	}
}

