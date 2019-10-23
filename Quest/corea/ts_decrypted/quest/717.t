CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 717;
	title = 71702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "3;";

			CDboTSActTWaitTS
			{
				taid = 2;
				time = 5000;
			}
			CDboTSActPCConv
			{
				taid = 1;
				tblidx = 71730;
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
				eitype = 6;
				esctype = 0;
				ectype = -1;
				etype = 1;
				taid = 1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 71708;
			gtype = 2;
			oklnk = 2;
			area = 71701;
			goal = 71704;
			sort = 71705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 71702;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 71707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 1551105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
			CDboTSCheckClrQst
			{
				and = "694;";
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 71714;
			nextlnk = 101;
			rwdtbl = 71701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1551105;
			}
		}
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "4;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 6;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSColRgn
			{
				widx = 1;
				cct = 1;
				crt = 0;
				r = "40.000000";
				x = "7045.000000";
				z = "-50.000000";
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
				conv = 71709;
				ctype = 1;
				idx = 1551105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 71708;
				gtype = 2;
				area = 71701;
				goal = 71704;
				grade = 132203;
				rwd = 100;
				sort = 71705;
				stype = 2;
				taid = 1;
				title = 71702;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 6;
				tidx0 = 508;
				ectype = -1;
				etype = 0;
				iidx0 = -1;
				it0 = 71702;
				taid = 3;
				widx0 = 1;
				dt0 = 71720;
				esctype = 0;
				otype0 = 7;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

