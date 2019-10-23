CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 411;
	title = 41102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 41108;
				gtype = 0;
				area = 41101;
				goal = 41104;
				grade = 132203;
				rwd = 100;
				sort = 41105;
				stype = 1;
				taid = 1;
				title = 41102;
			}
			CDboTSActNPCConv
			{
				conv = 41109;
				ctype = 1;
				idx = 8511104;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 41114;
			nextlnk = 254;
			rwdtbl = 41101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5041119;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 41107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8511104;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 11;
				minlvl = 3;
			}
			CDboTSCheckClrQst
			{
				and = "410;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 41108;
			gtype = 0;
			oklnk = 2;
			area = 41101;
			goal = 41104;
			sort = 41105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 41102;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

